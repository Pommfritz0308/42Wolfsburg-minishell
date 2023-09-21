#include "../includes/minishell.h"

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

	backslashes = 0;
	while (--pos >= 0 && s[pos] == '\\')
		backslashes++;
	return (backslashes % 2);
}

t_tocken_type	define_token_type(char *s, size_t i)
{
	if (s[i] == '(')
		return (PARANTH_OPEN);
	if (s[i] == ')')
		return (PARANTH_CLOSE);
	if (s[i] == '>' && s[i + 1] == '>')
		return (REDIR_APPEND);
	else if (s[i] == '>')
		return (REDIR_OUT);
	if (s[i] == '<' && s[i + 1] == '<')
		return (REDIR_HEREDOC);
	else if (s[i] == '<' && s[i + 1] == '>')
		return (REDIR_OPEN);
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

void	check_quotes_backslash(char *s, int (*f)[7])
{
	if ((*f)[0])
		(*f)[2] = 0;
	else
		(*f)[2] = is_backslash(s, (*f)[6]);
	if (s[(*f)[6]] == '\'' && !(*f)[1] && !(*f)[2])
		(*f)[0] = !(*f)[0];
	else if (s[(*f)[6]] == '\"' && !(*f)[0] && !(*f)[2])
		(*f)[1] = !(*f)[1];
}

t_tocken	*last_token(char *s, int (*f)[7], size_t *pos, t_tocken **t)
{
	*pos = (*f)[6] + 1;
	if ((*f)[5])
	{
		(*t)->val = str_unquote(str_slice(s, (*f)[3], (*f)[6]));
		return (*t);
	}
	free(*t);
	return (0);
}
