/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <anasser-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:54:52 by anasser-          #+#    #+#             */
/*   Updated: 2024/09/17 15:55:58 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*complete_single(char *new, char *str, t_var *var)
{
	char	c;

	while (*str)
	{
		if (*str == '\'')
		{
			new = chng(new, ft_strjoin(new, get_string(++str, var)));
			return (new);
		}
		c = *str;
		new = ft_strjoin(new, &c);
		str++;
	}
	return (new);
}

char	*complete_double(char *new, char *str, t_var *var)
{
	char	c;

	while (*str)
	{
		if (*str == '\"')
		{
			new = chng(new, ft_strjoin(new, get_string(++str, var)));
			return (new);
		}
		else if (*str == '$')
		{
			new = chng(new,
					ft_strjoin(new, get_from_env(var->env, read_env(str))));
			str += to_next(str);
		}
		else
		{
			c = *str;
			new = ft_strjoin(new, &c);
		}
	}
	return (new);
}

char	*complete(char *new, char *str, t_var *var, char tocmpl)
{
	if (tocmpl == '\'')
		return (complete_single(new, ++str, var));
	else
		return (complete_double(new, ++str, var));
}

char	*get_string(char *str, t_var *var)
{
	char	*new;
	char	c[2];

	new = ft_strdup("");
	if (str == NULL || !*str || !check_quotes(str))
		return (new);
	while (*str != '\0')
	{
		if (*str == '\'' || *str == '\"')
			return (complete(new, str, var, *str));
		else if (*str == '$' && *(str + 1) == '?')
		{
			new = chng(new, ft_strjoin(new, ft_itoa(var->last)));
			str += 2;
		}
		else if (*str == '$')
		{
			new = chng(new,
					ft_strjoin(new, get_from_env(var->env, read_env(str))));
			str += to_next(str);
		}
		else
		{
			c[0] = *str;
			c[1] = '\0';
			new = chng(new, ft_strjoin(new, c));
			str++;
		}
	}
	return (new);
}
