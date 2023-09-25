#include "../includes/minishell.h"

void	handle_cond(t_tree **ast, t_tocken *token, int (*f)[2])
{
	if (!(*ast)->token && !(*ast)->redirections)
		(*ast)->token = token;
	else
		add_new_head(ast, token);
	(*f)[0] = 0;
	(*f)[1] = 1;
}

int	check_token_type(t_tocken_type curr, t_tocken_type prev)
{
	if (curr == PIPE && prev > PARANTH_CLOSE)
		return (ft_perror(0, SY_PIPE, 0));
	if ((curr == AND || curr == OR) && prev > PARANTH_CLOSE)
		return (ft_perror(0, SYNTAX, 0));
	if ((curr == PARANTH_OPEN && prev < PARANTH_OPEN && prev != START))
		return (ft_perror(0, SYNTAX, 0));
	return (1);
}

t_tree	*build_ast(char *s, size_t *i)
{
	t_tocken		*token;
	t_tree			*ast;
	int				f[2];
	t_tocken_type	prev_token_type;
	t_tocken_type	curr;

	ast = new_tree_node();
	token = next_token(s, i);
	if (token && (token->type == AND || token->type == OR
		|| token->type == PIPE || token->type == PARANTH_CLOSE))
	{
		ft_perror(0, SYNTAX, 0);
		return (0);
	}
	prev_token_type = START;
	f[0] = 0;
	f[1] = 1;
	while (token)
	{
		curr = token->type;
		if (!check_token_type(token->type, prev_token_type))
			return (0);
		if (token->type == PIPE)
			handle_pipe(&ast, token, &f);
		else if (token->type == AND || token->type == OR)
			handle_cond(&ast, token, &f);
		else if (token->type == PARANTH_OPEN)
		{
			if (!handle_paranth(&ast, &f, i, s))
				return (0);
		}
		else if (token->type == PARANTH_CLOSE)
			return (ast);
		else
		{
			if (!handle_command(&token, s, i, &f, &ast, prev_token_type))
				return (0);
			prev_token_type = curr;
			continue ;
		}
		prev_token_type = curr;
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
	if (!ast)
		env->curr_exit_code = 258;
	free(buf);
	return (ast);
}
