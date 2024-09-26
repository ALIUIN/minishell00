/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_controle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <anasser-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 09:25:36 by anasser-          #+#    #+#             */
/*   Updated: 2024/09/23 17:04:40 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_line *line, t_var *var, int *fd, char *in)
{
	int		filein;

	filein = -1;
	if (in != NULL)
		filein = open(in, O_RDONLY, 0777);
	if (filein == -1)
		error();
	if (fd)
		dup2(fd[1], STDOUT_FILENO);
	if (in != NULL)
		dup2(filein, STDIN_FILENO);
	if (fd)
		close(fd[0]);
	try(line, var, -1);
}

void	parent_process(t_line *line, t_var *var, int *fd, char *out)
{
	int		fileout;

	if (!line)
		return ;
	fileout = -1;
	if (out != NULL)
		fileout = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		error();
	if (fd)
		dup2(fd[0], STDIN_FILENO);
	if (out != NULL)
		dup2(fileout, STDOUT_FILENO);
	if (fd)
		close(fd[1]);
	try(line, var, -1);
}

t_line	*find_in(t_line *line)
{
	while (line)
	{
		if (line->isbest)
			return (line);
		line = line->next;
	}
	return (NULL);
}
t_line	*find_out(t_line *line)
{
	while (line)
	{
		if (line->isbestout)
			return (line);
		line = line->next;
	}
	return (NULL);
}

int	pipe_it(t_line *f, t_line *sec, t_var *var)
{
	int		fd[2];
	pid_t	pid1;
	int		status;
	t_line	*l;

	printf("here\n");
	sleep(1);
	if (pipe(fd) == -1)
		error();
	pid1 = fork();
	if (pid1 == -1)
		error();
	l = find_in(f);
	if (pid1 == 0 && l)
		child_process(f, var, fd, l->cmd);
	else if (pid1 == 0)
		child_process(f, var, fd, NULL);
	printf("child pass\n");
	l = find_out(sec);
	waitpid(pid1, &status, 0);
	if (status == 0 && l)
		parent_process(sec, var, fd, l->cmd);
	else if (status == 0)
		parent_process(sec, var, fd, NULL);
	else
		ft_putstr_fd("\033[31mError: Bad comands\n\e[0m", 2);
	return (0);
}
