/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_controle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasser- <anasser-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:53:46 by anasser-          #+#    #+#             */
/*   Updated: 2024/09/23 16:42:40 by anasser-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_from_env(char **envp, char *tofind)
{
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], tofind, ft_strlen(tofind)) == 0)
		i++;
	if (!envp[i])
		return ("");
	return (envp[i] + ft_strlen(tofind) + 1);
}
