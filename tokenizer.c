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

	if (!s  || *pos >= ft_strlen(s))
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
