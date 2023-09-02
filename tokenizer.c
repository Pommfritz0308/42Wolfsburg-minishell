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

t_tree	*tokenize(char *s)
{
	int				s_d_quote[2];
	int				paranthesis;
	int				backslash;
	int				token_start;
	t_parser_state	state;
	int				i;
	t_tocken		*token;

	s_d_quote[0] = 0;
	s_d_quote[1] = 0;
	paranthesis = 0;
	backslash = 0;
	token_start = -1;
	state = SPACE_;
	i = -1;
	token = new_tocken();
	while (s && s[++i])
	{
		if (s_d_quote[0])
			backslash = 0;
		else
			backslash = is_backslash(s, i);
		if (s[i] == '\'' && !s_d_quote[1] && !backslash)
			s_d_quote[0] = !s_d_quote[0];
		else if (s[i] == '\"' && !s_d_quote[0] && !backslash)
			s_d_quote[1] = !s_d_quote[1];
		else if (s[i] == '(' && !s_d_quote[0] && !s_d_quote[1] && !backslash)
			paranthesis++;
		else if (s[i] == ')' && !s_d_quote[0] && !s_d_quote[1] && !backslash)
			paranthesis--;
		else if (s[i] == '&' && s[i + 1] == '&' && !s_d_quote[0] && !s_d_quote[1] && !backslash)
		{
			state = AND_;
			i++;
		}
		else if (s[i] == '|' && s[i + 1] == '|' && !s_d_quote[0] && !s_d_quote[1] && !backslash)
		{
			state = OR_;
			i++;
		}
		else if (s[i] == '|' && !s_d_quote[0] && !s_d_quote[1] && !backslash)
			state = PIPE_;
		else if (s[i] == '>' && s[i + 1] == '>' && !s_d_quote[0] && !s_d_quote[1] && !backslash)
		{
			state = REDIRECTION_;
			i++;
		}
		else if (s[i] == '<' && s[i + 1] == '<' && !s_d_quote[0] && !s_d_quote[1] && !backslash)
		{
			state = REDIRECTION_;
			i++;
		}
		else if (s[i] == '<' && s[i + 1] == '>' && !s_d_quote[0] && !s_d_quote[1] && !backslash)
		{
			state = REDIRECTION_;
			i++;
		}
		else if (s[i] == '>' && !s_d_quote[0] && !s_d_quote[1] && !backslash)
			state = REDIRECTION_;
		else if (s[i] == '<' && !s_d_quote[0] && !s_d_quote[1] && !backslash)
			state = REDIRECTION_;
		if ((s[i] == ' ' || s[i] == '\t' || s[i] == '|' || s[i] == '&' || s[i] == '>' || s[i] == '<') && !s_d_quote[0] && !s_d_quote[1] && !backslash)
		{
			if (state != SPACE_)
			{
				token->val = slice_str(s, token_start, state != TOKEN_ ? i - 2 : i - 1);
				printf("Token %d val: |%s|\n", token->type, token->val);
				token = new_tocken();
				token_start = -1;
			}
			if (state != TOKEN_ && state != SPACE_)
			{
				token->type = (t_tocken_type)state;
				printf("Token %d val: |%s|\n", token->type, token->val);
				token = new_tocken();
			}
			state = SPACE_;
		}
		else
		{
			state = TOKEN_;
			if (token_start == -1)
				token_start = i;
		}
	}
	if (state == TOKEN_)
	{
		token->val = slice_str(s, token_start, i);
		printf("Token %d val: |%s|\n", token->type, token->val);
	}
	return (0);
}
