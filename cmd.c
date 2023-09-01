/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:21:11 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/01 12:31:25 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd_node(void)
{
	t_cmd	*res;

	res = (t_cmd *)malloc(sizeof(t_cmd));
	if (!res)
		return (0);
	res->next_cmd = 0;
	res->out_rdrcts = 0;
	res->in_rdrcts = 0;
	return (res);
}

t_rdrct	*new_rdrct_node(void)
{
	t_rdrct	*res;

	res = (t_rdrct *)malloc(sizeof(t_rdrct));
	if (!res)
		return (0);
	res->next = 0;
	res->heredoc = 0;
	res->in_fd = -1;
	res->out_fd = -1;
	res->stderr_to_1 = 0;
	return (res);
}
