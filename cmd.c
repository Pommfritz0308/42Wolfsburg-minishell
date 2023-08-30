/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:21:11 by psimonen          #+#    #+#             */
/*   Updated: 2023/08/30 16:23:20 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd_node()
{
	t_cmd	*res;

	res = (t_cmd *)malloc(sizeof(t_cmd));
	if (!res)
		return (0);
	res->next_cmd = 0;
	return (res);
}