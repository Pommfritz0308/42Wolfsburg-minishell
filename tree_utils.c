#include "minishell.h"

t_tree	*new_tree_node(void)
{
	t_tree	*node;

	node = (t_tree *)malloc(sizeof(t_tree));
	if (!node)
		return (0);
	node->left = 0;
	node->right = 0;
	node->tocken = 0;
	node->args = 0;
	node->redirections = 0;
	return (node);
}

void	add_new_head(t_tree **ast, t_tocken *token)
{
	t_tree	*node;

	node = new_tree_node();
	node->tocken = token;
	node->left = *ast;
	*ast = node;
}

void	paste_tree(t_tree *ast, t_tree *subtree)
{
	t_tree	*node;

	if (ast->right)
	{
		node = new_tree_node();
		node->left = ast->right;
		ast->right = node;
		node->right = subtree;
	}
	else
		ast->right = subtree;
}

void	paste_node(t_tree *ast, t_tree *node)
{
	if (!ast->tocken)
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
	t_tree *node = new_tree_node();
	node->tocken = token;
	paste_node(ast, node);
	return (node);
}

void	paste_redir_word(t_rdr_l *redirs, char *word)
{
	while(redirs->next)
		redirs = redirs->next;
	redirs->word = word;
}

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

void	paste_redir(t_rdr_l **redirs, t_tocken *token)
{
	t_rdr_l *tail;

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
