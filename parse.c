/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:53:37 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/01 12:33:06 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_by_char(char *s, char sep)
{
	s = 0;
	sep = 0;
	return (0);
}

void	parse(char *user_input, t_cmd **cmds)
{
	char	**commands;
	t_cmd	*buf;

	commands = split_by_char(resolve_env(user_input), '|');
	buf = *cmds;
	while (*commands)
	{
		if (!buf)
			*cmds = parse_cmd(*commands);
		else
		{
			buf->next_cmd = parse_cmd(*commands);
			buf = buf->next_cmd;
		}
		commands++;
	}
}
