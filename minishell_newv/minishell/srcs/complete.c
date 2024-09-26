/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <anasser-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:53:38 by anasser-          #+#    #+#             */
/*   Updated: 2024/09/17 15:53:39 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	other(char c)
{
	if (c == '\'')
		return ('"');
	return ('\'');
}

char	*chng(char *old, char *new)
{
	free(old);
	return (new);
}

bool	check_quotes(char *str)
{
	int		len;
	char	*stack;
	int		s;
	int		i;

	len = ft_strlen(str);
	i = 0;
	stack = ft_calloc((len + 1), sizeof(char));
	s = -1;
	while (i < len)
	{
		if (s > -1 && str[i] == stack[s])
			s--;
		else if (str[i] == '\'' || str[i] == '"')
		{
			s++;
			stack[s] = str[i];
		}
		i++;
	}
	free(stack);
	if (s > -1)
		return (false);
	return (true);
}

int	to_next(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != ' '
		&& str[i] != '\t' && str[i] != '\n')
	{
		i++;
	}
	return (i);
}

char	*read_env(char *str)
{
	char	*ret;
	int		i;

	if (*str == '$')
		str++;
	i = to_next(str);
	ret = malloc((i + 1) * sizeof(char));
	ft_strlcpy(ret, str, i + 1);
	return (ret);
}
