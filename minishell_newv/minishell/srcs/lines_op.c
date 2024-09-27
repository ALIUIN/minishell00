/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <anasser-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 08:20:55 by anasser-          #+#    #+#             */
/*   Updated: 2024/09/23 17:13:48 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_special(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&');
}

void	free_node(t_line *node)
{
	free(node->arg);
	free(node->arg);
	free(node);
}

t_line	*new(char *cmd, bool isopp)
{
	t_line	*new;

	new = malloc(sizeof(t_line));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->arg = ft_strdup("");
	new->cmd = cmd;
	new->isopp = isopp;
	new->isbest = false;
	new->isbestout = false;
	return (new);
}

t_line	*get_last(t_line *head)
{
	if (head == NULL || head->next == NULL)
		return (head);
	return (get_last(head->next));
}

void	append(t_line **head, t_line *new)
{
	t_line	*h;

	h = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (h->next)
	{
		h = h->next;
	}
	h->next = new;
}

void	token(t_line **line, char *cmd, t_var *var, bool isopp)
{
	t_line	*last;
	char	*cur;
	char	*ss;

	if (isopp)
		append(line, new(ft_strdup(cmd), isopp));
	else
	{
		if (*line == NULL)
			last = *line;
		else
			last = get_last(*line);
		if (last == NULL || *(last->cmd) == '|')
			append(line, new(ft_strdup(cmd), false));
		else
		{
			cur = ft_strdup("");
			if (ft_strlen(last->arg))
			{
				free(cur);
				cur = ft_strjoin(last->arg, " ");
			}
			free(last->arg);
			ss = get_string(cmd, var);
			last->arg = ft_strjoin(cur, ss);
			free(ss);
			free(cur);
		}
	}
}

t_line	*init_line(char *cmd, t_var *var)
{
	char	**cmds;
	int		i;
	t_line	*line;

	i = 0;
	line = NULL;
	cmds = ft_special_split(cmd);
	while (cmds[i])
	{
		token(&line, cmds[i], var, is_special(*cmds[i]));
		i++;
	}
	i = 0;
	while (cmds[i])
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
	sort_list(line);
	return (line);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	error(void)
{
	perror("\033[31mError");
	exit(-1);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split((const char *)argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		printf("error");
	free(path);
}

void	execute_child(char *argv, char **envp)
{
	int	pid;
	int	status;

	pid = fork();
	if (!pid)
	{
		execute(argv, envp);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
t_line	*split_to_pipe(t_line *line)
{
	t_line	*cur;
	t_line	*tmp;
	t_line	*l;

	cur = line;
	tmp = NULL;
	while (cur->next)
	{
		if (*(cur->next->cmd) && (*(cur->next->cmd) == '|'))
		{
			tmp = cur->next->next;
			l = cur->next;
			l->next = NULL;
			cur->next = NULL;
			free_line(l);
			break ;
		}
		cur = cur->next;
	}
	return (tmp);
}

/*
	function to devellop
*/

void	read_heredoc(char *arg)
{
	heredoc(arg);
}
void	change_io(t_line *in, t_line *out)
{
	int		fin;
	int		fout;

	if (in != NULL && ft_strlen(in->cmd) == 1)
		fin = open(in->arg, O_RDONLY, 0777);
	else if (in != NULL && ft_strlen(in->cmd) == 2)
		read_heredoc(in->arg);
	if (out != NULL && ft_strlen(out->cmd) == 1)
		fout = open(out->arg, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (out != NULL && ft_strlen(out->cmd) == 2)
		fout = open(out->arg, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (out != NULL)
		dup2(fout, STDOUT_FILENO);
	if (in != NULL)
		dup2(fin, STDIN_FILENO);
}
void	exec_ce(char *c, t_var *var, t_line *in, t_line *out)
{
	int	pid;

	pid = fork();
	if (pid)
	{
		change_io(in, out);
		execute(c, var->env);
	}
	else
		waitpid(pid, &(var->last), 0);
}
void	process_it(t_line *cur, t_var *var, t_line *in, t_line *out)
{
	char	*c;
	char	*tmp;
	t_line	*ne;

	while (cur)
	{
		ne = cur->next;
		if (!cur->isopp)
		{
			if (!exec_builtin(cur, var))
			{
				tmp = ft_strjoin(cur->cmd, " ");
				c = ft_strjoin(tmp, cur->arg);
				free(tmp);
				exec_ce(c, var, in, out);
				free(c);
			}
		}
		free_line(cur);
		cur = ne;
	}
}

// for edit

void	try(t_line *cur, t_var *var, int write_fd)
{
	t_line	*sp;

	sp = split_to_pipe(cur);
	if (sp)
		pipe_it(cur, sp, var);
	else
		process_it(cur, var, find_in(cur), find_out(cur));
	if (write_fd > 0)
		write_t_var(write_fd, var);
	//free_line(sp);
}
void	free_line(t_line *line)
{
	t_line	*l;

	while (line)
	{
		l = line->next;
		free(line->cmd);
		free(line->arg);
		free(line);
		line = l;
	}
}
int	go_try(char *cmds, t_var *var)
{
	t_line	*line;
	int		pid;
	int		pipe_fd[2];

	if (!cmds || !var->env)
	{
		if (cmds)
			free(cmds);
		return (-1);
	}
	line = init_line(cmds, var);
	t_line	*cur = line;
	while (cur)
	{
		printf("%s : %s\n", cur->cmd, cur->arg);
		cur = cur->next;
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		try(line, var, pipe_fd[1]);
		close(pipe_fd[1]);
	}
	else
	{
		close(pipe_fd[1]);
		free_var(var);
		read_t_var(pipe_fd[0], var);
		waitpid(pid, &(var->last), 0);
		change_after_pipe(var);
		close(pipe_fd[0]);
		free_line(line);
	}
	return (0);
}
