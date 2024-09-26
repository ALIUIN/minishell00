#include "../minishell.h"

void	write_t_var(int fd, t_var *var)
{
	size_t	len;
	size_t	env_count;
	int		i;

	write(fd, &var->last, sizeof(var->last));
	len = ft_strlen(var->pn) + 1;
	write(fd, &len, sizeof(len));
	write(fd, var->pn, len);
	len = ft_strlen(var->name) + 1;
	write(fd, &len, sizeof(len));
	write(fd, var->name, len);
	len = ft_strlen(var->cwd) + 1;
	write(fd, &len, sizeof(len));
	write(fd, var->cwd, len);
	len = ft_strlen(var->usr) + 1;
	write(fd, &len, sizeof(len));
	write(fd, var->usr, len);
	env_count = 0;
	i = 0;
	if (var->env)
	{
		while (var->env[env_count])
			env_count++;
		write(fd, &env_count, sizeof(env_count));
		while (i < env_count)
		{
			len = strlen(var->env[i]) + 1;
			write(fd, &len, sizeof(len));
			write(fd, var->env[i], len);
			i++;
		}
	}
	else
		write(fd, &env_count, sizeof(env_count));
}
void	read_t_var(int fd, t_var *var)
{
	size_t	len;
	int		i;
	size_t	env_count;

	read(fd, &var->last, sizeof(var->last));
	read(fd, &len, sizeof(len));
	var->pn = malloc(len);
	read(fd, var->pn, len);
	read(fd, &len, sizeof(len));
	var->name = malloc(len);
	read(fd, var->name, len);
	read(fd, &len, sizeof(len));
	var->cwd = malloc(len);
	read(fd, var->cwd, len);
	read(fd, &len, sizeof(len));
	var->usr = malloc(len);
	read(fd, var->usr, len);
	i = 0;
	read(fd, &env_count, sizeof(env_count));
	var->env = malloc((env_count + 2) * sizeof(char*));
	var->env[env_count + 1] = NULL;
	while (i < env_count)
	{
		read(fd, &len, sizeof(len));
		var->env[i] = malloc(len);
		read(fd, var->env[i], len);
		i++;
	}
}
