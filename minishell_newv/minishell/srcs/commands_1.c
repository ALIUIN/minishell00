/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <anasser-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:53:13 by anasser-          #+#    #+#             */
/*   Updated: 2024/09/23 17:29:25 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	if (*s1 || *s2)
		return (1);
	return (0);
}
void	ft_strcpy(char *dest, char *send)
{
	while (*send)
	{
		*dest = *send;
		send++;
		dest++;
	}
	*dest = '\0';
}

void	env(char **envp)
{
	char	**env;

	env = envp;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

bool	is_valid_name(char *name)
{
	if (!ft_isalpha(*name) && *name != '_')
		return (false);
	name++;
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (false);
		name++;
	}
	return (true);
}

void	export(char *args, t_var *var)
{
	char	**argv;
	int		i;

	i = 0;
	argv = ft_split(args, '=');
	while (argv[i] != NULL)
		i++;
	if (i != 2 || !set(argv[0], argv[1], var))
	{
		printf("export: not a valid identifier: %s\n", args);
		var->last = 1;
		return ;
	}
	free(argv[0]);
	free(argv[1]);
	free(argv[2]);
	var->cwd = get_from_env(var->env, "PWD");
	var->pn = print_mini(var->name, var->usr, var->cwd);
	var->last = 0;
}

void	unset(char *args, t_var *var)
{
	char	**argv;

	argv = ft_split(args, '=');
	delete_from_env(argv[0], var->env);
	free(argv[0]);
	free(argv[1]);
	free(argv[2]);
	var->cwd = get_from_env(var->env, "PWD");
	var->pn = print_mini(var->name, var->usr, var->cwd);
	var->last = 0;
}

void	pwd(t_var *var)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("getcwd");
	}
	var->last = 0;
}

bool	set(char *name, char *value, t_var *var)
{
	int		i;
	char	*new;

	new = get_from_env(var->env, name);
	i = 0;
	if (!is_valid_name(name))
	{
		var->last = 1;
		return (false);
	}
	if (ft_strlen(new) > 0)
		ft_strcpy(new, value);
	else
	{
		while (var->env[i] != NULL)
		{
			i++;
		}
		var->env[i] = ft_strjoin(name, ft_strjoin("=", value));
		var->env[i + 1] = NULL;
	}
	var->pn = print_mini(var->name, var->usr, var->cwd);
	var->last = 0;
	return (true);
}

void	delete_from_env(char *name, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0)
		{
			envp[i] = "";
			break ;
		}
		i++;
	}
	while (envp[i + 1] != NULL)
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = envp[i + 1];
}
void	change_after_pipe(t_var *var)
{
	char	*new;
	char	cwd[1024];

	new = get_from_env(var->env, "PWD");
	cd(new, var);
	printf("\nh\n%s\n", new);
	var->pn = print_mini(var->name, var->usr, new);
}
void	changewd(t_var *var)
{
	char	*old;
	char	*new;
	char	cwd[1024];

	old = get_from_env(var->env, "OLDPWD");
	new = get_from_env(var->env, "PWD");
	getcwd(cwd, sizeof(cwd));
	free(var->cwd);
	var->cwd = ft_strdup(cwd);
	if (ft_strcmp(new, cwd))
		ft_strcpy(new, cwd);
	printf("%s\n", new);
	var->pn = print_mini(var->name, var->usr, cwd);
}

void	cd(char *path, t_var *var)
{
	char	*home;
	int		status;

	status = 0;
	if (path == NULL || ft_strlen(path) == 0 || ft_strcmp(path, "~") == 0)
	{
		home = get_from_env(var->env, "HOME");
		status = chdir(home);
		if (status != 0)
			perror("chdir");
	}
	else
	{
		status = chdir(path);
		if (status != 0)
			perror("chdir");
	}
	printf("finish cd\n");
	changewd(var);
	var->last = status;
}

void	echo(char *line, bool withline, t_var *var)
{
	if (line != NULL)
	{
		if (withline)
			printf("%s\n", line);
		else
			printf("%s", line);
	}
	else
	{
		if (withline)
			printf("%s\n", line);
	}
	var->last = 0;
}

bool	exec_builtin(t_line *line, t_var *var)
{
	if (ft_strncmp(line->cmd, "cd", 2) == 0)
		cd(line->arg, var);
	else if (ft_strncmp(line->cmd, "pwd", 3) == 0)
		pwd(var);
	else if (ft_strncmp(line->cmd, "env", 3) == 0)
		env(var->env);
	else if (ft_strncmp(line->cmd, "echo", 4) == 0)
	{
		if (ft_strncmp(line->arg, "-n", 2) == 0)
			echo(line->arg + 2, false, var);
		else
			echo(line->arg, true, var);
	}
	else if (ft_strncmp(line->cmd, "export", 6) == 0)
		export(line->arg, var);
	else if (ft_strncmp(line->cmd, "unset", 5) == 0)
		unset(line->arg, var);
	else
		return (false);
	return (true);
}
