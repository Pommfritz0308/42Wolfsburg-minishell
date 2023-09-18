#include "minishell.h"

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

int	is_digit(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

void	switch_remove(int *var, char *s, int *i)
{
	int	j;
	int	k;

	if (*var == 0)
		*var = 1;
	else
		*var = 0;
	j = *i + 1;
	k = -1;
	while (s[j + ++k])
		s[*i + k] = s[j + k];
	s[*i + k] = 0;
	(*i)--;
}

char	*str_unquote(char *s)
{
	int	i;
	int	sd[3];

	i = -1;
	sd[0] = 0;
	sd[1] = 0;
	sd[2] = 0;
	while (s && s[++i])
	{
		sd[2] = is_backslash(s, i);
		if (s[i] == '\'' && !sd[0] && !sd[1] && !sd[2])
			switch_remove(sd, s, &i);
		else if (s[i] == '\'' && sd[0])
			switch_remove(sd, s, &i);
		else if (s[i] == '"' && !sd[0] && !sd[1] && !sd[2])
			switch_remove(sd + 1, s, &i);
		else if (s[i] == '"' && sd[1] && !sd[2])
			switch_remove(sd + 1, s, &i);
	}
	return (s);
}
