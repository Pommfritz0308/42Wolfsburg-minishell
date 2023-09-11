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

t_tree	*new_node(void)
{
	t_tree	*node;

	node = (t_tree *)malloc(sizeof(t_tree));
	if (!node)
		return (0);
	node->left = 0;
	node->right = 0;
	node->tocken = 0;
	return (node);
}

int	is_backslash(char *s, int pos)
{
	int	backslashes;

	if (!pos)
		return (0);
	backslashes = 0;
	while (--pos && s[pos] == '\\')
		backslashes++;
	if (backslashes % 2 == 1)
		return (1);
	return (0);
}

char	*slice_str(char *s, int start, int end)
{
	char	*res;
	int		i;

	res = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (0);
	i = -1;
	while (start + ++i <= end)
		res[i] = s[start + i];
	res[i] = 0;
	return (res);
}

int	str_contains(char c, char *s)
{
	while (s && *s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

t_tocken_type	define_token_type(char *s, size_t i)
{
	if (s[i] == '(')
		return (PARANTH_OPEN);
	if (s[i] == ')')
		return (PARANTH_CLOSE);
	if (s[i] == '>')
		return (REDIR_OUT);
	if (s[i] == '<' && s[i + 1] == '<')
		return (REDIR_HEREDOC);
	else if (s[i] == '<' && s[i + 1] == '>')
		return (REDIR_CLOSE);
	else if (s[i] == '<')
		return (REDIR_IN);
	if (s[i] == '&' && s[i + 1] == '&')
		return (AND);
	if (s[i] == '|' && s[i + 1] == '|')
		return (OR);
	else if (s[i] == '|')
		return (PIPE);
	return (WORD);
	
}

t_tocken	*next_token(char *s, size_t *pos)
{
	int				s_d_quote[2];
	int				backslash;
	int				token_start;
	int				operator_start;
	t_parser_state	state;
	char			*operator;
	size_t			i;
	t_tocken		*token;

	if (*pos >= ft_strlen(s))
		return (0);
	s_d_quote[0] = 0;
	s_d_quote[1] = 0;
	backslash = 0;
	token_start = -1;
	state = SPACE_;
	i = *pos;
	token = new_tocken();
	token->type = WORD;
	while (s && s[i])
	{
		operator_start = -1;
		operator = 0;
		if (s_d_quote[0])
			backslash = 0;
		else
			backslash = is_backslash(s, i);
		if (s[i] == '\'' && !s_d_quote[1] && !backslash)
			s_d_quote[0] = !s_d_quote[0];
		else if (s[i] == '\"' && !s_d_quote[0] && !backslash)
			s_d_quote[1] = !s_d_quote[1];
		//if (s[i] == '$' && !s_d_quote[0] && !backslash && ft_isalnum(s[i + 1]))
		if ((str_contains(s[i], " \t|><()") || (s[i] == '&' && s[i + 1] == '&'))
			&& !s_d_quote[0] && !s_d_quote[1] && !backslash)
		{
			token->type = define_token_type(s, i);
			if (str_contains(s[i], "<>"))
			{
				operator_start = i;
				if (i - 1 >= 0 & s[i - 1] == '&')
					operator_start--;
				while (--operator_start >= 0 && ft_isdigit(s[operator_start]))
					;
				operator_start++;
				if ((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i + 1] == '<')
					|| (s[i] == '<' && s[i + 1] == '>') || (s[i] == '>' && s[i + 1] == '|'))
					i++;
				if (s[i + 1] == '&')
					i++;
				token->val = slice_str(s, operator_start, i);
				*pos = i + 1;
				return (token);
			}
			else if (str_contains(s[i], "|&()"))
			{
				operator_start = i;
				if ((s[i] == '&' && s[i + 1] == '&') || (s[i] == '|' && s[i + 1] == '|'))
					i++;
				token->val = slice_str(s, operator_start, i);
				*pos = i + 1;
				return (token);
			}
			if (state == TOKEN_)
			{
				*pos = i;
				if (operator_start == -1)
					token->val = slice_str(s, token_start, i - 1);
				else if (operator_start > token_start)
				{
					free(operator);
					*pos = operator_start;
					token-> val = slice_str(s, token_start, operator_start - 1);
				}
				return (token);
			}
			*pos = i + 1;
			if (token->val)
				return (token);
			token_start = -1;
			state = SPACE_;
		}
		else
		{
			state = TOKEN_;
			if (token_start == -1)
				token_start = i;
		}
		i++;
	}
	*pos = i + 1;
	if (state == TOKEN_)
	{
		token -> val = slice_str(s, token_start, i);
		return (token);
	}
	free(token);
	return (0);
}

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

char	last_char(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	if (s && i > 0)
		return (s[i - 1]);
	return (0);
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
				free (token);
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
