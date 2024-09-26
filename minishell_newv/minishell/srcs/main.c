/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <anasser-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:58:34 by anasser-          #+#    #+#             */
/*   Updated: 2024/09/21 17:24:54 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

t_var	*create(t_var *vari)
{
	static t_var	*var = NULL;

	if (vari != NULL)
		var = vari;
	return (var);
}

char	*get_user(char **envp)
{
	return (get_from_env(envp, "LOGNAME"));
}

char	*print_mini(char *n, char *usr, char *cwd)
{
	char	*name;
	char	*tmp;

	tmp = ft_strjoin("", "\033[32m$\033[32m\033[31m[\033[31m");
	name = ft_strjoin(tmp, "\033[32m");
	free(tmp);
	tmp = ft_strjoin(name, usr);
	free(name);
	name = ft_strjoin(tmp, "\033[32m\033[31m@\033[31m\033[32m");
	free(tmp);
	tmp = ft_strjoin(name, n);
	free(name);
	name = ft_strjoin(tmp, "\033[32m\033[31m]\033[31m\033[32m:");
	free(tmp);
	tmp = ft_strjoin(name, cwd);
	free(name);
	name = ft_strjoin(tmp, " \033[32m>>\033[0m");
	free(tmp);
	return (name);
}
void	in_execution(t_var *var)
{
	char	*input;

	while (true)
	{
		input = readline(var->pn);
		if (input == NULL )
			break ;
		if (*input)
			add_history(input);
		if (*input == '\0')
			continue ;
		if (ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			break ;
		}
		go_try(input, var);
		rl_on_new_line();
		free(input);
	}
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

t_var	*init(char **argv, char **envp)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	var->argv = argv;
	var->env = envp;
	var->name = var->argv[0] + 2;
	var->usr = get_user(var->env);
	var->cwd = malloc(1024 * sizeof(char));
	getcwd(var->cwd, 1024);
	var->pn = print_mini(var->name, var->usr, var->cwd);
	var->last = 0;
	var = create(var);
	return (var);
}
void	free_var(t_var *var)
{
	free(var->cwd);
	free(var->pn);
}

int	main(int argc, char **argv, char **envp)
{
	t_var	*var;

	var = init(argv, envp);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	if (argc < 0 || argc > 1)
		return (1);
	if (!envp)
		return (1);
	in_execution(var);
	rl_clear_history();
	free_var(var);
	return (0);
}
