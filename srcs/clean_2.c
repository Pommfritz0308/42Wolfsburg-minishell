/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:00 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/27 12:29:03 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*clean_tree_tok(t_tree *tree, t_tocken *token)
{
	if (tree)
		clean_tree(tree);
	if (token)
		clean_token(token);
	return (0);
}

void	clean_pids(t_pidlst *pids)
{
	t_pidlst	*buf;

	if (!pids)
		return ;
	while (pids)
	{
		buf = pids;
		pids = pids->next;
		free(buf);
	}
}
