#include "../includes/minishell.h"

void	paste_paranth(t_tree **ast, t_tree *subtree)
{
	t_tree	*node;

	if (!(*ast)->token)
		node = *ast;
	else
		node = new_tree_node();
	node->token = new_tocken();
	node->token->type = PARANTH_OPEN;
	node->right = subtree;
	if (node == *ast)
		return ;
	if ((*ast)->right)
	{
		node->left = *ast;
		*ast = node;
	}
	else
		(*ast)->right = node;
}

void	paste_node(t_tree *ast, t_tree *node)
{
	if (!ast->token)
	{
		node->left = ast->left;
		ast->left = node;
	}
	else
	{
		node->right = ast->right;
		ast->right = node;
	}
}

t_tree	*paste_token(t_tree *ast, t_tocken *token)
{
	t_tree	*node;

	if (!ast->token)
	{
		node = ast;
		node->token = token;
	}
	else
	{
		node = new_tree_node();
		node->token = token;
		paste_node(ast, node);
	}
	return (node);
}

void	paste_redir_word(t_rdr_l *redirs, char *word)
{
	while (redirs->next)
		redirs = redirs->next;
	redirs->word = word;
}

void	paste_redir(t_rdr_l **redirs, t_tocken *token)
{
	t_rdr_l	*tail;

	if (!*redirs)
	{
		*redirs = new_redir(token);
		return ;
	}
	tail = *redirs;
	while (tail->next)
		tail = tail->next;
	tail->next = new_redir(token);
}
