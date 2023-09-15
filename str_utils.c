#include "minishell.h"

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

char	*str_join(char const *s1, char const *s2, char *sep)
{
	char	*res;
	int		s1_len;
	int		s2_len;
	int		sep_len;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	sep_len = ft_strlen(sep);
	res = (char *)ft_calloc(s1_len + s2_len + sep_len + 1, sizeof(char));
	if (!res)
		return (0);
	res = ft_memcpy(res, s1, s1_len);
	ft_memcpy(res + s1_len, sep, sep_len);
	ft_memcpy(res + s1_len + sep_len, s2, s2_len);
	return (res);
}

static int	add_word(const char *s, char **dest, char c)
{
	int	len;
	int	i;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	*dest = (char *)ft_calloc(len + 1, sizeof(char));
	if (!(*dest))
		return (-1);
	i = -1;
	while (++i < len)
		(*dest)[i] = s[i];
	return (1);
}

static int	count_words(const char *s, char c, char **res)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			if (res && add_word(s + i, res + len, c) == -1)
				return (-1);
			len++;
			while (s[i] && s[i] != c)
				i++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (len);
}

char	**str_split(char const *s, char c)
{
	int		count;
	char	**res;

	if (!s)
		return (0);
	count = count_words(s, c, 0);
	res = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!res)
		return (0);
	if (count_words(s, c, res) == -1)
	{
		count = -1;
		while (res[++count])
			free(res[count]);
		free(res);
		return (0);
	}
	return (res);
}

char	*str_unescape(char *s)
{
	int		len;
	int		i;
	char	*res;

	len = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\\' && str_contains(s[i + 1], "\"\'\\"))
			continue ;
		len++;
	}
	res = (char *)ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (0);
	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] == '\\' && str_contains(s[i + 1], "\"\'\\"))
			continue ;
		res[len] = s[i];
		len++;
	}
	return (res);
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

char	*str_cut(char *s, size_t start, size_t end)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (0);
	ft_strlcpy(res, s + start, end - start + 1);
	return (res);
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