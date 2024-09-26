/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdakdouk <hdakdouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:28:27 by hdakdouk          #+#    #+#             */
/*   Updated: 2024/09/22 17:09:10 by hdakdouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define BUFFER_SIZE 1024

// Custom handler for interrupt signals (Ctrl+C)
void handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\nHeredoc interrupted. Exiting...\n", 33);
		exit(1);
	}
}

// Custom readline function using allowed functions
char *custom_readline(const char *prompt)
{
	int		index;
	char	ch;
	char *line;

	index = 0;
	line = malloc(BUFFER_SIZE);
	if (!line)
		return (NULL);

	write(STDOUT_FILENO, prompt, strlen(prompt));

	//try to use get_next_line instead of read function
	while (read(STDIN_FILENO, &ch, 1) > 0 && ch != '\n' && index < BUFFER_SIZE - 1)
	{
		line[index++] = ch;
	}
	line[index] = '\0';

	// If input was interrupted (Ctrl+D), return NULL
	if (index == 0 && ch == '\0')
	{
		free(line);
		return (NULL);
	}

	return (line);
}

// Function to handle heredoc input until the specified delimiter
void heredoc(const char *delimiter)
{
	char *line;
	const char *filename;
	int fd;

	// Handle interrupts gracefully
	signal(SIGINT, handle_signals);
	filename = "heredoc.txt"; // Use a fixed file name for storing heredoc content
	// Create or overwrite the file to store heredoc content
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("Error creating heredoc file");
		exit(EXIT_FAILURE);
	}

	// Read lines until the delimiter is encountered
	while (1)
	{
		line = custom_readline("> ");
		if (!line)
		{
			write(STDOUT_FILENO, "Error reading input\n", 20);
			close(fd);
			unlink(filename);
			exit(EXIT_FAILURE);
		}

		// Check if the input matches the delimiter
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}

		// Write the line to the file
		write(fd, line, strlen(line));
		write(fd, "\n", 1); // Add newline to mimic normal input
		free(line);
	}

	// Close and reopen the file to set it up for reading
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening heredoc file");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO); // Redirect standard input to the heredoc file
	close(fd);

	// Free resources and delete the file after use
	unlink(filename); // Remove the heredoc file after processing
}
