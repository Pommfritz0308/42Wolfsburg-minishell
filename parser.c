# include "minishell.h"

t_tree	*build_ast(char *s, size_t *i)
{
	t_tocken	*token;
	t_tree		*ast;
	t_tree		*buf;
	int			prev_tocken;
	int			redir_ready;

	ast = new_tree_node();
	token = next_token(s, i);
	prev_tocken = 0;
	redir_ready = 1;
	buf = 0;
	while (token)
	{
		if (token->type == AND || token->type == OR || token->type == PIPE)
		{
			if (!ast->tocken)
				ast->tocken = token;
			else
				add_new_head(&ast, token);
			prev_tocken = 0;
			redir_ready = 1;
		}
		else if (token->type == PARANTH_OPEN)
		{
			paste_tree(ast, build_ast(s, i));
			prev_tocken = 0;
			redir_ready = 1;
		}
		else if (token->type == PARANTH_CLOSE)
			return (ast);
		else
		{
			if (!prev_tocken)
				buf = paste_token(ast, 0);
			if (token->type == WORD)
			{
				if (!redir_ready)
					paste_redir_word(buf->redirections, token->val);
				ft_lstadd_back(&buf->args, ft_lstnew(token->val));
				redir_ready = 1;
				if (!buf->tocken)
					buf->tocken = token;
				else
					free(token);
			}
			else
			{
				redir_ready = 0;
				if (ft_isdigit(last_char(token->val)))
					redir_ready = 1;
				paste_redir(&buf->redirections, token);
			}
			prev_tocken = 1;
		}
		token = next_token(s, i);
	}
	return (ast);
}

t_tree	*ast(char *s)
{
	size_t	i;

	i = 0;
	return (build_ast(s, &i));
}

void	print_ast(char *s)
{
	size_t	i;

	i = 0;
	print_tree(build_ast(s, &i));
}
