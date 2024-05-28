/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:06 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/27 12:29:07 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_tab(char **t)
{
	int	i;

	i = -1;
	while (t[++i])
		free(t[i]);
	free(t);
}

void	clean_token(t_tocken *t)
{
	if (!t)
		return ;
	if (t->val)
		free(t->val);
	free(t);
}

void	clean_redirections(t_rdr_l *r)
{
	t_rdr_l	*buf;

	while (r)
	{
		if (r->word)
			free(r->word);
		clean_token(r->token);
		buf = r;
		r = r->next;
		free(buf);
	}
}

void	clean_str(void	*str)
{
	if (str)
		free(str);
}

void	clean_tree(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		clean_tree(tree->left);
	if (tree->right)
		clean_tree(tree->right);
	if (tree->redirections)
		clean_redirections(tree->redirections);
	if (tree->token)
		clean_token(tree->token);
	if (tree->args)
		ft_lstclear(&tree->args, clean_str);
	free(tree);
}
