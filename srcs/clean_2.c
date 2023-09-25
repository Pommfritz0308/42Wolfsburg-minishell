#include "minishell.h"

t_tree	*clean_tree_tok(t_tree *tree, t_tocken *token)
{
	if (tree)
		clean_tree(tree);
	if (token)
		clean_token(token);
	return (0);
}
