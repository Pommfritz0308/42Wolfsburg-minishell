#include "minishell.h"

t_tocken	*new_tocken(void)
{
	t_tocken	*tocken;

	tocken = (t_tocken *)malloc(sizeof(t_tocken));
	if (!tocken)
		return (0);
	tocken->val = 0;
	tocken->type = WORD;
	return (tocken);
}

t_tree	*tokenize(char *s)
{
	int	s_d_quote[2];
	int	paranthesis;
	int	token_start = 0;

	s_d_quote[0] = 0;
	s_d_quote[1] = 0;
	paranthesis = 0;
	t_tree *node = new_node();
	if (!node)
		return(0);
	node->left = new_node();
	node->left->tocken = new_tocken();
	node->left->tocken->val = "Value";
}