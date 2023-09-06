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

void	lexer(char *s)
{
	int				s_d_quote[2];
	int				backslash;
	int				token_start;
	t_parser_state	state;
	char			*token;
	int				i;

	s_d_quote[0] = 0;
	s_d_quote[1] = 0;
	backslash = 0;
	token_start = -1;
	state = SPACE_;
	i = -1;
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
		if ((str_contains(s[i], " \t|><()") || (s[i] == '&' && s[i + 1] == '&'))
			&& !s_d_quote[0] && !s_d_quote[1] && !backslash)
		{
			if (state == TOKEN_)
			{
				token = slice_str(s, token_start, i - 1);
				printf("Token val: |%s|\n", token);
			}
			if (str_contains(s[i], "|&><()"))
			{
				token_start = i;
				if ((s[i] == '&' && s[i + 1] == '&') || (s[i] == '|' && s[i + 1] == '|')
					|| (s[i] == '>' && s[i + 1] == '>')
					|| (s[i] == '<' && s[i + 1] == '<') || (s[i] == '<' && s[i + 1] == '>'))
					i++;
				token = slice_str(s, token_start, i);
				printf("Token val: |%s|\n", token);
			}
			token_start = -1;
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
		token = slice_str(s, token_start, i);
		printf("Token val: |%s|\n", token);
	}
}
