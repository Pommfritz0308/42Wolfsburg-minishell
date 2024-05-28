/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:30:22 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/27 12:30:24 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*str_slice(char *s, int start, int end)
{
	char	*res;
	int		i;

	res = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!res)
		return (0);
	i = -1;
	while (start + ++i <= end)
		res[i] = s[start + i];
	res[i] = 0;
	return (res);
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
