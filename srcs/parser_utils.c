#include "minishell.h"

void	handle_word_helper(t_tree **buf, t_tocken *token, int (*fpci)[5])
{
	if (!(*fpci)[1])
		paste_redir_word((*buf)->redirections, ft_strdup(token->val));
	else
	{
		ft_lstadd_back(&(*buf)->args, ft_lstnew(ft_strdup(token->val)));
		if (!(*buf)->token)
			(*buf)->token = token;
	}
	(*fpci)[1] = 1;
	if ((*buf)->token != token)
		clean_token(token);
}

void	handle_word(t_tree **buf, t_tocken *token, t_tree *ast, int (*fpci)[5])
{
	if (ast->token && (ast->token->type == AND || ast->token->type == OR))
	{
		if (!ast->right)
			ast->right = new_tree_node();
		ast = ast->right;
	}
	if (!(*fpci)[0] && (*fpci)[2] != (int)PARANTH_CLOSE)
		*buf = paste_token(ast, 0);
	else if (!(*fpci)[0])
		*buf = ast;
	if (token->type == WORD)
		handle_word_helper(buf, token, fpci);
	else
	{
		(*fpci)[1] = 0;
		if (ft_isdigit(last_char(token->val)))
			(*fpci)[1] = 1;
		paste_redir(&(*buf)->redirections, token);
	}
	(*fpci)[0] = 1;
}

void	handle_pipe(t_tree **ast, t_tocken *token, int (*fpci)[5])
{
	t_tree	*node;

	if (*ast && !(*ast)->token && !((*ast)->redirections))
		(*ast)->token = token;
	else if ((*ast)->redirections || ((*ast)->token
			&& (*ast)->token->type != AND && (*ast)->token->type != OR))
		add_new_head(ast, token);
	else
	{
		node = new_tree_node();
		node->token = token;
		node->left = (*ast)->right;
		(*ast)->right = node;
	}
	(*fpci)[0] = 0;
	(*fpci)[1] = 1;
}

int	handle_paranth(t_tree **ast, char *s, int (*fpci)[5])
{
	t_tree	*subtree;

	subtree = build_ast(s, fpci);
	if (!subtree)
		return (0);
	if (!subtree->token)
	{
		clean_tree(subtree);
		return (0);
	}
	if ((*ast)->token
		&& ((*ast)->token->type == AND || (*ast)->token->type == OR))
	{
		if (!(*ast)->right)
			(*ast)->right = new_tree_node();
		paste_paranth(&((*ast)->right), subtree);
	}
	else
		paste_paranth(ast, subtree);
	(*fpci)[0] = 0;
	(*fpci)[1] = 1;
	return (1);
}

int	handle_command(t_tocken **token, char *s, t_tree **ast, int (*fpci)[5])
{
	t_tree	*buf;

	buf = 0;
	while (*token && (*token)->type <= REDIR_HEREDOC)
	{
		handle_word(&buf, *token, *ast, fpci);
		*token = next_token(s, *fpci + 4);
	}
	if (!(*fpci)[1])
		return (ft_perror(0, SYNTAX, 0));
	if ((*fpci)[2] == (int)PARANTH_CLOSE && buf && buf->args)
		return (ft_perror(0, SYNTAX, 0));
	return (1);
}
