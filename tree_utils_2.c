#include "minishell.h"

t_rdr_l	*new_redir(t_tocken *token)
{
	t_rdr_l	*res;

	res = (t_rdr_l *)malloc(sizeof(t_rdr_l));
	if (!res)
		return (0);
	res->next = 0;
	res->token = token;
	res->word = 0;
	return (res);
}

t_tree	*new_tree_node(void)
{
	t_tree	*node;

	node = (t_tree *)malloc(sizeof(t_tree));
	if (!node)
		return (0);
	node->left = 0;
	node->right = 0;
	node->token = 0;
	node->args = 0;
	node->redirections = 0;
	return (node);
}

void	add_new_head(t_tree **ast, t_tocken *token)
{
	t_tree	*node;

	node = new_tree_node();
	node->token = token;
	node->left = *ast;
	*ast = node;
}
