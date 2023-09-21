#include "../includes/minishell.h"

void	operator_helper(char *s, int (*f)[7], size_t *pos, t_tocken *token)
{
	if ((*f)[3] != -1 && (*f)[4] > (*f)[3])
	{
		*pos = (*f)[4];
		token->type = WORD;
		token->val = str_slice(s, (*f)[3], (*f)[4] - 1);
	}
	else
	{
		*pos = (*f)[6] + 1;
		token->val = str_slice(s, (*f)[4], (*f)[6]);
	}
}

t_tocken	*operator(char *s, int (*f)[7], size_t *pos, t_tocken *token)
{
	(*f)[4] = (*f)[6];
	token->type = define_token_type(s, (*f)[6]);
	if (str_contains(s[(*f)[6]], "<>"))
	{
		if ((*f)[6] >= 1 && s[(*f)[6] - 1] == '&')
			(*f)[4]--;
		while (--(*f)[4] >= 0 && ft_isdigit(s[(*f)[4]]))
			;
		(*f)[4]++;
		if ((s[(*f)[6]] == '>' && s[(*f)[6] + 1] == '>')
			|| (s[(*f)[6]] == '<' && s[(*f)[6] + 1] == '<')
			|| (s[(*f)[6]] == '<' && s[(*f)[6] + 1] == '>')
			|| (s[(*f)[6]] == '>' && s[(*f)[6] + 1] == '|'))
			(*f)[6]++;
		if (s[(*f)[6] + 1] == '&')
			(*f)[6]++;
	}
	else if ((s[(*f)[6]] == '&' && s[(*f)[6] + 1] == '&')
		|| (s[(*f)[6]] == '|' && s[(*f)[6] + 1] == '|'))
		(*f)[6]++;
	operator_helper(s, f, pos, token);
	return (token);
}

t_tocken	*next_token_helper(char *s, size_t *pos, int (*f)[7], t_tocken **t)
{
	while (s && s[(*f)[6]])
	{
		check_quotes_backslash(s, f);
		if ((str_contains(s[(*f)[6]], "|><()") || (s[(*f)[6]] == '&'
			&& s[(*f)[6] + 1] == '&')) && !(*f)[0] && !(*f)[1] && !(*f)[2])
			return (operator(s, f, pos, *t));
		if (str_contains(s[(*f)[6]], " \t") && !(*f)[0] && !(*f)[1] && !(*f)[2])
		{
			*pos = (*f)[6] + 1;
			(*t)->val = str_slice(s, (*f)[3], (*f)[6] - 1);
			return (*t);
		}
		(*f)[5] = 1;
		if ((*f)[3] == -1)
			(*f)[3] = (*f)[6];
		(*f)[6]++;
	}
	(*t)->val = 0;
	return (*t);
}

/*
	f[0] - single quote
	f[1] - double quote
	f[2] - backspace
	f[3] - token_start
	f[4] - operator_start
	f[5] - state (0 whitespace, 1 word)
	f[6] - iterator
*/
t_tocken	*next_token(char *s, size_t *pos)
{
	int				f[7];
	t_tocken		*token;

	if (!s || *pos >= ft_strlen(s))
		return (0);
	f[0] = 0;
	f[1] = 0;
	f[2] = 0;
	f[3] = -1;
	f[5] = 0;
	f[6] = *pos;
	token = new_tocken();
	token->type = WORD;
	while (s && s[f[6]] && str_contains(s[f[6]], " \t"))
		f[6]++;
	token = next_token_helper(s, pos, &f, &token);
	if (token->val)
	{
		token->val = str_unquote(token->val);
		return (token);
	}
	return (last_token(s, &f, pos, &token));
}
