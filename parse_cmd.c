/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:08:52 by psimonen          #+#    #+#             */
/*   Updated: 2023/08/30 18:14:23 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_flag(char *flags, char curr)
{
	static char	flag;
	int			res;

	res = 0;
	if (flag)
		res = 1;
	while (*flags)
	{
		if (*flags == curr)
		{
			if (flag == curr)
				flag = 0;
			else if (!flag)
				flag = curr;
		}
		flags++;
	}
	return (res);
}

void	parse_out(char *s, int i, t_cmd *res)
{
	s = 0;
	i = 0;
	res = 0;
	return ;
}

t_cmd	*parse_cmd(char *s)
{
	int		i;
	t_cmd	*res;

	res = new_cmd_node();
	i = -1;
	while (s[++i])
	{
		if (s[i] == '>' && !check_flag("\'\"", s[i]))
		{
			parse_out(s, i, res);
		}
		else if (s[i] == '<' && !check_flag("\'\"", s[i]))
		{

		}
	}
	return (res);
}
