#include "minishell.h"

void	handle_word(t_tree **buf, int (*f)[2], t_tocken *token, t_tree *ast)
{
	if (!(*f)[0])
		*buf = paste_token(ast, 0);
	if (token->type == WORD)
	{
		if (!(*f)[1])
			paste_redir_word((*buf)->redirections, token->val);
		else
			ft_lstadd_back(&(*buf)->args, ft_lstnew(token->val));
		(*f)[1] = 1;
		if (!(*buf)->tocken)
			(*buf)->tocken = token;
		else
			free(token);
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

void	handle_op(t_tree **ast, t_tocken *token, int (*f)[2])
{
	if (!(*ast)->tocken)
		(*ast)->tocken = token;
	else
		add_new_head(ast, token);
	(*f)[0] = 0;
	(*f)[1] = 1;
}

void	handle_paranth(t_tree **ast, int (*f)[2], size_t *i, char *s)
{
	paste_tree(*ast, build_ast(s, i));
	(*f)[0] = 0;
	(*f)[1] = 1;
}

t_tree	*build_ast(char *s, size_t *i)
{
	t_tocken	*token;
	t_tree		*ast;
	t_tree		*buf;
	int			f[2];

	ast = new_tree_node();
	token = next_token(s, i);
	f[0] = 0;
	f[1] = 1;
	buf = 0;
	while (token)
	{
		if (token->type == AND || token->type == OR || token->type == PIPE)
			handle_op(&ast, token, &f);
		else if (token->type == PARANTH_OPEN)
			handle_paranth(&ast, &f, i, s);
		else if (token->type == PARANTH_CLOSE)
			return (ast);
		else
			handle_word(&buf, &f, token, ast);
		token = next_token(s, i);
	}
	return (ast);
}

t_tree	*ast(char *s)
{
	size_t	i;
	t_tree	*ast;
	char	*buf;

	i = 0;
	buf = resolve_env(s);
	ast = build_ast(buf, &i);
	free(buf);
	return (ast);
}

void	print_ast(char *s)
{
	size_t	i;

	i = 0;
	print_tree(build_ast(s, &i));
}
