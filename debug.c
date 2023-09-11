#include "minishell.h"

void	print_t_rdrct(t_rdrct *node)
{
	printf(
		"T_rdrct %p\nHeredoc:\t%d\nin_fd:\t\t%d\nlimiter:\t%s\nnext:\t\t%p\n"\
		"open_flags:\t%d\nout_fd:\t\t%d\nstderr_to_1:\t%d\nword:\t\t%s\n\n",
		node,
		node->heredoc,
		node->in_fd,
		node->limiter,
		node->next,
		node->open_flags,
		node->out_fd,
		node->stderr_to_1,
		node->word
	);
}

void	print_tree_helper(t_tree *tree, int pos)
{
	int i;

	i = -1;
	while (++i < pos)
		printf("\t");
	if (tree && tree->tocken)
		printf(
			"<%lx %d: %s (%lx %lx)>",
			((unsigned long)tree) % 0x1000,
			tree->tocken->type,
			tree->tocken->val,
			((unsigned long)tree->left) % 0x1000,
			((unsigned long)tree->right) % 0x1000
		);
	else if (tree)
		printf(
			"<%lx (null) (%lx %lx)>",
			((unsigned long)tree) % 0x1000,
			((unsigned long)tree->left) % 0x1000,
			((unsigned long)tree->right) % 0x1000
		);
	printf("\n");
	if (!tree || (!tree->left && !tree->right))
		return ;
	if (tree)
	{
		print_tree_helper(tree->left, pos - 1);
		if (tree->left)
			printf("\n");
		print_tree_helper(tree->right, pos + 1);
	}
}

int		tree_depth(t_tree *tree)
{
	int	left;
	int	right;

	if (!tree)
		return (0);
	if (!tree->left && !tree->right)
		return (1);
	left = tree_depth(tree->left);
	right = tree_depth(tree->right);
	if (left > right)
		return(left + 1);
	return (right + 1);
}

void	print_tree(t_tree *tree)
{
	print_tree_helper(tree, tree_depth(tree));
}