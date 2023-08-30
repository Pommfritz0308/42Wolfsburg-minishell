/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:49:08 by psimonen          #+#    #+#             */
/*   Updated: 2023/08/30 12:50:17 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*resolve_env(char *s)
{
	int	inside_quote;
	int	i;

	inside_quote = 0;
	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '\'')
		{
			if (inside_quote)
				inside_quote = 0;
			else
				inside_quote = 1;
			continue ;
		}
		if (s[i] == '$' && ft_isalnum(s[i+1]))
		{
			i++;
		}
	}
	return (0);
}