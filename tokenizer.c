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

void	check_quotes_backslash(char *s, int (*sdbtosi)[7])
{
	if ((*sdbtosi)[0])
		(*sdbtosi)[2] = 0;
	else
		(*sdbtosi)[2] = is_backslash(s, (*sdbtosi)[6]);
	if (s[(*sdbtosi)[6]] == '\'' && !(*sdbtosi)[1] && !(*sdbtosi)[2])
		(*sdbtosi)[0] = !(*sdbtosi)[0];
	else if (s[(*sdbtosi)[6]] == '\"' && !(*sdbtosi)[0] && !(*sdbtosi)[2])
		(*sdbtosi)[1] = !(*sdbtosi)[1];
}

t_tocken	*next_token(char *s, size_t *pos)
{
	int				sdbtosi[7]; // 0 Single quote | 1 double quote | 2 backspace | 3 token_start | 4 operator_start | 5 state | 6 i
	t_tocken		*token;

	if (!s  || *pos >= ft_strlen(s))
		return (0);
	sdbtosi[0] = 0;
	sdbtosi[1] = 0;
	sdbtosi[2] = 0;
	sdbtosi[3] = -1;
	sdbtosi[5] = 1;
	sdbtosi[6] = *pos;
	token = new_tocken();
	token->type = WORD;
	while (s && s[sdbtosi[6]] && str_contains(s[sdbtosi[6]], " \t"))
		sdbtosi[6]++;
	while (s && s[sdbtosi[6]])
	{
		check_quotes_backslash(s, &sdbtosi);
		//if (s[i] == '$' && !s_d_quote[0] && !backslash && ft_isalnum(s[i + 1]))
		if ((str_contains(s[sdbtosi[6]], "|><()") || (s[sdbtosi[6]] == '&' && s[sdbtosi[6] + 1] == '&'))
			&& !sdbtosi[0] && !sdbtosi[1] && !sdbtosi[2])
		{
			sdbtosi[4] = sdbtosi[6];
			token->type = define_token_type(s, sdbtosi[6]);
			if (str_contains(s[sdbtosi[6]], "<>"))
			{
				if (sdbtosi[6] >= 1 && s[sdbtosi[6] - 1] == '&')
					sdbtosi[4]--;
				while (--sdbtosi[4] >= 0 && ft_isdigit(s[sdbtosi[4]]))
					;
				sdbtosi[4]++;
				if ((s[sdbtosi[6]] == '>' && s[sdbtosi[6] + 1] == '>') || (s[sdbtosi[6]] == '<' && s[sdbtosi[6] + 1] == '<')
					|| (s[sdbtosi[6]] == '<' && s[sdbtosi[6] + 1] == '>') || (s[sdbtosi[6]] == '>' && s[sdbtosi[6] + 1] == '|'))
					sdbtosi[6]++;
				if (s[sdbtosi[6] + 1] == '&')
					sdbtosi[6]++;
			}
			else if ((s[sdbtosi[6]] == '&' && s[sdbtosi[6] + 1] == '&') || (s[sdbtosi[6]] == '|' && s[sdbtosi[6] + 1] == '|'))
				sdbtosi[6]++;
			if (sdbtosi[3] != -1 && sdbtosi[4] > sdbtosi[3])
			{
				*pos = sdbtosi[4];
				token->type = WORD;
				token-> val = slice_str(s, sdbtosi[3], sdbtosi[4] - 1);
			}
			else
			{
				*pos = sdbtosi[6] + 1;
				token->val = slice_str(s, sdbtosi[4], sdbtosi[6]);
			}
			return (token);
		}
		else if (str_contains(s[sdbtosi[6]], " \t") && !sdbtosi[0] && !sdbtosi[1] && !sdbtosi[2])
		{
			*pos = sdbtosi[6] + 1;
			token->val = slice_str(s, sdbtosi[3], sdbtosi[6] - 1);
			return (token);
		}
		else
		{
			sdbtosi[5] = 0;
			if (sdbtosi[3] == -1)
				sdbtosi[3] = sdbtosi[6];
		}
		sdbtosi[6]++;
	}
	*pos = sdbtosi[6] + 1;
	if (sdbtosi[5] == 0)
	{
		token -> val = slice_str(s, sdbtosi[3], sdbtosi[6]);
		return (token);
	}
	free(token);
	return (0);
}
