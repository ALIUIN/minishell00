/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <anasser-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 08:21:30 by anasser-          #+#    #+#             */
/*   Updated: 2024/09/23 17:02:52 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./ft_printf/ft_printf.h"
# include <stdio.h>       // printf, perror
# include <stdlib.h>      // malloc, free, exit, getenv
# include <unistd.h>
# include <fcntl.h>       // open, O_* constants
# include <sys/types.h>   // fork, wait, waitpid
# include <sys/wait.h>    // wait, waitpid, wait3, wait4
# include <signal.h>      // signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>    // stat, lstat, fstat, unlink
# include <string.h>      // strerror
# include <termios.h>     // tcsetattr, tcgetattr
# include <dirent.h>      // opendir, readdir, closedir
# include <errno.h>       // errno
# include <term.h>        // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <sys/ioctl.h>   // ioctl
# include <readline/readline.h>    // readline, rl_clear_history
# include <readline/history.h>     // add_history
# include <stdbool.h>

typedef struct s_var
{
	char	**argv;
	char	**env;
	char	*pn;
	char	*name;
	char	*cwd;
	char	*usr;
	int		last;
}		t_var;

typedef struct s_line
{
	char			*cmd;
	char			*arg;
	bool			isopp;
	bool			isbest;
	bool			isbestout;
	struct s_line	*next;
}	t_line;

bool	exec_builtin(t_line *line, t_var *var);
void	try(t_line *cur, t_var *var, int write_fd);
char	*get_from_env(char **envp, char *tofind);
bool	set(char *name, char *value, t_var *var);
char	*print_mini(char *n, char *usr, char *cwd);
void	delete_from_env(char *name, char **envp);
int		ft_strcmp(char *s1, char *s2);
char	*get_string(char *str, t_var *var);
char	*read_env(char *str);
bool	check_quotes(char *str);
char	*chng(char *old, char *new);
char	other(char c);
int		to_next(char *str);
char	**ft_special_split(char *line);
int		go_try(char *cmds, t_var *var);
t_line	*new(char *cmd, bool isopp);
void	free_node(t_line *node);
void	sort_list(t_line *line);
int		pipe_it(t_line *f, t_line *sec, t_var *var);
void	error(void);
t_line	*find_out(t_line *line);
t_line	*find_in(t_line *line);
void	free_line(t_line *l);
t_var	*create(t_var *vari);
void	free_var(t_var *var);
void	write_t_var(int fd, t_var *var);
void	read_t_var(int fd, t_var *var);
void	changewd(t_var *var);
void	cd(char *path, t_var *var);
void	change_after_pipe(t_var *var);
/**/
void	heredoc(const char *delimiter);
char	*custom_readline(const char *prompt);
void	handle_signals(int sig);
/**/

#endif