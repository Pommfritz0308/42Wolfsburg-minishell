#include "../includes/minishell.h"
/*
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

int	check_init(t_tocken *token, t_tocken_type (*prev_curr)[2], int (*f)[2])
{
	if (token && (token->type == AND || token->type == OR
		|| token->type == PIPE || token->type == PARANTH_CLOSE))
		return (ft_perror(0, SYNTAX, 0));
	(*prev_curr)[0] = START;
	(*f)[0] = 0;
	(*f)[1] = 1;
	return (1);
}

t_tree	*build_ast(char *s, size_t *i)
{
	t_tocken		*token;
	t_tree			*ast;
	int				f[2];
	t_tocken_type	prev_curr[2];

	ast = new_tree_node();
	token = next_token(s, i);
	if (!check_init(token, &prev_curr, &f))
		return (clean_tree_tok(ast, token));
	while (token)
	{
		prev_curr[1] = token->type;
		if (!check_token_type(token->type, prev_curr[0]))
			return (clean_tree_tok(ast, token));
		if (token->type == PARANTH_CLOSE)
			return (ast);
		else if (token->type == PIPE)
			handle_pipe(&ast, token, &f);
		else if (token->type == AND || token->type == OR)
			handle_cond(&ast, token, &f);
		else if (token->type == PARANTH_OPEN)
		{
			if (!handle_paranth(&ast, &f, i, s))
				return (clean_tree_tok(ast, token));
		}
		else
		{
			if (!handle_command(&token, s, i, &f, &ast, prev_curr[0]))
				return (clean_tree_tok(ast, 0));
			prev_curr[0] = prev_curr[1];
			continue ;
		}
		prev_curr[0] = prev_curr[1];
		token = next_token(s, i);
	}
	return (ast);
}
*/

void	handle_cond(t_tree **ast, t_tocken *token, int (*fcpi)[5])
{
	if (!(*ast)->token && !(*ast)->redirections)
		(*ast)->token = token;
	else
		add_new_head(ast, token);
	(*fcpi)[0] = 0;
	(*fcpi)[1] = 1;
}

int	check_token_type(int (*fpci)[5])
{
	if ((*fpci)[3] == (int)PIPE && (*fpci)[2] > (int)PARANTH_CLOSE)
		return (ft_perror(0, SY_PIPE, 0));
	if (((*fpci)[3] == (int)AND || (*fpci)[3] == (int)OR)
		&& (*fpci)[2] > (int)PARANTH_CLOSE)
		return (ft_perror(0, SYNTAX, 0));
	if (((*fpci)[3] == (int)PARANTH_OPEN
		&& (*fpci)[2] < (int)PARANTH_OPEN && (*fpci)[2] != (int)START))
		return (ft_perror(0, SYNTAX, 0));
	return (1);
}

int	build_ast_helper(t_tree **ast, t_tocken **token, char *s, int (*fpci)[5])
{
	(*fpci)[3] = (int)(*token)->type;
	if (!check_token_type(fpci))
		return (0);
	if ((*token)->type == PARANTH_CLOSE)
		return (1);
	else if ((*token)->type == PIPE)
		handle_pipe(ast, *token, fpci);
	else if ((*token)->type == AND || (*token)->type == OR)
		handle_cond(ast, *token, fpci);
	else if ((*token)->type == PARANTH_OPEN)
	{
		if (!handle_paranth(ast, s, fpci))
			return (0);
		clean_token(*token);
	}
	else
	{
		if (!handle_command(token, s, ast, fpci))
			return (3);
		(*fpci)[2] = (*fpci)[3];
		return (2);
	}
	(*fpci)[2] = (*fpci)[3];
	return (4);
}

t_tree	*build_ast(char *s, int (*fpci)[5])
{
	t_tocken	*token;
	t_tree		*ast;
	int			res;

	ast = new_tree_node();
	token = next_token(s, *fpci + 4);
	if (token && (token->type == AND || token->type == OR || token->type == PIPE
			|| token->type == PARANTH_CLOSE) && ft_perror(0, SYNTAX, 1))
		return (clean_tree_tok(ast, token));
	while (token)
	{
		res = build_ast_helper(&ast, &token, s, fpci);
		if (!res)
			return (clean_tree_tok(ast, token));
		else if (res == 1)
		{
			clean_token(token);
			return (ast);
		}
		else if (res == 2)
			continue ;
		else if (res == 3)
			return (clean_tree_tok(ast, 0));
		token = next_token(s, *fpci + 4);
	}
	return (ast);
}

/*
	fpci[0] = f[0]
	fpci[1] = f[1]
	fpci[2] = prev_curr[0]
	fpci[3] = prev_curr[1]
	fpci[4] = i
*/
t_tree	*ast(char *s, t_env *env)
{
	t_tree	*ast;
	char	*buf;
	int		fpci[5];

	fpci[4] = 0;
	fpci[0] = 0;
	fpci[1] = 1;
	fpci[2] = (int)START;
	buf = resolve_env(s, env);
	ast = build_ast(buf, &fpci);
	if (!ast)
		env->curr_exit_code = 258;
	free(buf);
	return (ast);
}
