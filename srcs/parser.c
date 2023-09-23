#include "../includes/minishell.h"

void	handle_word(t_tree **buf, int (*f)[2], t_tocken *token, t_tree *ast)
{
	if (ast->token && (ast->token->type == AND || ast->token->type == OR))
	{
		if (!ast->right)
			ast->right = new_tree_node();
		ast = ast->right;
	}
	if (!(*f)[0])
		*buf = paste_token(ast, 0);
	if (token->type == WORD)
	{
		if (!(*f)[1])
			paste_redir_word((*buf)->redirections, ft_strdup(token->val));
		else
		{
			ft_lstadd_back(&(*buf)->args, ft_lstnew(ft_strdup(token->val)));
			if (!(*buf)->token)
				(*buf)->token = token;
		}
		(*f)[1] = 1;
		if ((*buf)->token != token)
			clean_token(token);
	}
	else
	{
		(*f)[1] = 0;
		if (ft_isdigit(last_char(token->val)))
			(*f)[1] = 1;
		paste_redir(&(*buf)->redirections, token);
	}
	(*f)[0] = 1;
}

void	handle_pipe(t_tree **ast, t_tocken *token, int (*f)[2])
{
	t_tree	*node;

	if (!(*ast)->token)
		(*ast)->token = token;
	else if ((*ast)->token->type != AND && (*ast)->token->type != OR)
		add_new_head(ast, token);
	else
	{
		node = new_tree_node();
		node->token = token;
		node->left = (*ast)->right;
		(*ast)->right = node;
	}
	(*f)[0] = 0;
	(*f)[1] = 1;
}

void	handle_paranth(t_tree **ast, int (*f)[2], size_t *i, char *s)
{
	paste_tree(*ast, build_ast(s, i));
	(*f)[0] = 0;
	(*f)[1] = 1;
}

void	handle_cond(t_tree **ast, t_tocken *token, int (*f)[2])
{
	if (!(*ast)->token)
		(*ast)->token = token;
	else
		add_new_head(ast, token);
	(*f)[0] = 0;
	(*f)[1] = 1;
}

int	handle_command(t_tocken **token, char *s, size_t *i, int (*f)[2], t_tree **ast)
{
	t_tree		*buf;

	buf = 0;
	while (*token && (*token)->type <= REDIR_HEREDOC)
	{
		handle_word(&buf, f, *token, *ast);
		*token = next_token(s, i);
	}
	if (!(*f)[1])
		return (ft_perror(0, SYNTAX, 0));
	return (1);
}

int	check_token_type(t_tocken_type curr, t_tocken_type prev)
{
	if (curr == PIPE && prev > 7)
		return (ft_perror(0, SY_PIPE, 0));
	if ((curr == AND || curr == OR) && prev > 7)
		return (ft_perror(0, SYNTAX, 0));
	return (1);
}

t_tree	*build_ast(char *s, size_t *i)
{
	t_tocken		*token;
	t_tree			*ast;
	int				f[2];
	t_tocken_type	prev_token_type;

	ast = new_tree_node();
	token = next_token(s, i);
	prev_token_type = WORD;
	f[0] = 0;
	f[1] = 1;
	while (token)
	{
		if (!check_token_type(token->type, prev_token_type))
			return (0);
		prev_token_type = token->type;
		if (token->type == PIPE)
			handle_pipe(&ast, token, &f);
		else if (token->type == AND || token->type == OR)
			handle_cond(&ast, token, &f);
		else if (token->type == PARANTH_OPEN)
			handle_paranth(&ast, &f, i, s);
		else if (token->type == PARANTH_CLOSE)
			return (ast);
		else
		{
			if (!handle_command(&token, s, i, &f, &ast))
				return (0);
			continue ;
		}
		token = next_token(s, i);
	}
	return (ast);
}

t_tree	*ast(char *s, t_env *env)
{
	size_t	i;
	t_tree	*ast;
	char	*buf;

	i = 0;
	buf = resolve_env(s, env);
	ast = build_ast(buf, &i);
	//print_tree(ast);
	if (!ast)
		env->curr_exit_code = 258;
	free(buf);
	return (ast);
}
