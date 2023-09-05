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

char	*next_token(char *s, int *pos)
{
	int				s_d_quote[2];
	int				backslash;
	int				token_start;
	int				operator_start;
	t_parser_state	state;
	char			*operator;
	int				i;

	s_d_quote[0] = 0;
	s_d_quote[1] = 0;
	backslash = 0;
	token_start = -1;
	state = SPACE_;
	i = *pos;
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
		if ((str_contains(s[i], " \t|><()") || (s[i] == '&' && s[i + 1] == '&'))
			&& !s_d_quote[0] && !s_d_quote[1] && !backslash)
		{
			if (str_contains(s[i], "<>"))
			{
				operator_start = i;
				if (i - 1 >= 0 & s[i - 1] == '&')
					operator_start--;
				while (--operator_start >= 0 && ft_isdigit(s[operator_start]))
					;
				operator_start++;
				if ((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i + 1] == '<') || (s[i] == '<' && s[i + 1] == '>') || (s[i] == '>' && s[i + 1] == '|'))
					i++;
				operator = slice_str(s, operator_start, i);
			}
			else if (str_contains(s[i], "|&()"))
			{
				operator_start = i;
				if ((s[i] == '&' && s[i + 1] == '&') || (s[i] == '|' && s[i + 1] == '|'))
					i++;
				operator = slice_str(s, operator_start, i);
			}
			if (state == TOKEN_)
			{
				*pos = i;
				if (operator_start == -1)
					return (slice_str(s, token_start, i - 1));
				else if (operator_start > token_start)
				{
					free(operator);
					*pos = operator_start;
					return (slice_str(s, token_start, operator_start - 1));
				}
			}
			*pos = i + 1;
			if (operator)
				return (operator);
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
		return (slice_str(s, token_start, i));
	return (0);
}

void	tokenize(char *s)
{
	char	*token;
	int		i;

	token = next_token(s, &i);
	while (token)
	{
		printf("tok: %s\n", token);
		token = next_token(s, &i);
	}
}
