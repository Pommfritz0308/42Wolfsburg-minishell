/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:53:37 by psimonen          #+#    #+#             */
/*   Updated: 2023/08/30 12:54:19 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_by_char(char *s, char sep, int special_case)
{
	s = 0;
	sep = 0;
	special_case = 0;
	return (0);
}

t_cmd	*fill_cmd(char *s)
{
	s = 0;
	return (0);
}

void	parse(char *user_input, t_cmd *cmds)
{
	char	**commands;

	commands = split_by_char(resolve_env(user_input), '|', 1);
	while (*commands)
	{
		if (!cmds)
			cmds = fill_cmd(*commands);
		else
			cmds->next_cmd  = fill_cmd(*commands);
		commands++;
	}
}
