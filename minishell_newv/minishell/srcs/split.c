/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <anasser-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 08:20:43 by anasser-          #+#    #+#             */
/*   Updated: 2024/09/21 17:50:07 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
bool	is_special_here(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&' || c == ' ');
}
char	*find_close(char **line)
{
	int		count;
	char	c;
	char	*l;
	int		n;

	if (!line || !*line)
		return (NULL);
	count = 0;
	n = 0;
	l = *line;
	c = *l;
	while (*l && count < 2)
	{
		if (*l == c)
			count++;
		l++;
		n++;
	}
	if (count < 2)
		return (NULL);
	l = malloc((1 + n) * sizeof(char));
	ft_strlcpy(l, *line, n + 1);
	*line += n;
	return (l);
}

char	*get_next_word(char **line)
{
	char	*l;
	int		n;

	if (!line || !*line)
		return (NULL);
	n = 0;
	l = *line;
	while (*l && !is_special_here(*l) && !(*l == '\'' || *l == '"'))
	{
		l++;
		n++;
	}
	l = malloc((n + 1) * sizeof(char));
	ft_strlcpy(l, *line, n + 1);
	*line += n;
	return (l);
}
int	handle_special(char **line, char **ret, int i)
{
	char	*l;
	int		n;

	if (!line || !*line)
		return (i);
	n = 0;
	l = *line;
	if (*l == ' ')
	{
		*line += 1;
		return (i);
	}
	while (*l && is_special_here(*l) && *l != ' ')
	{
		n++;
		l++;
	}
	l = malloc((n + 1) * sizeof(char));
	ft_strlcpy(l, *line, n + 1);
	*line += n;
	ret[i++] = l;
	return (i);
}

char	**ft_special_split(char *line)
{
	char	**ret;
	int		i;

	if (!line)
		return (NULL);
	i = 0;
	ret = ft_calloc((ft_strlen(line) + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	while (*line)
	{
		if (*line == '\'' || *line == '"')
			ret[i] = find_close(&line);
		else if (!is_special_here(*line))
			ret[i] = get_next_word(&line);
		if (ret[i])
			i++;
		if (is_special_here(*line))
			i = handle_special(&line, ret, i);
	}
	ret[i] = NULL;
	return (ret);
}
