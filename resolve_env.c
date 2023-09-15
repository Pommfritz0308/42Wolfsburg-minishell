/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:49:08 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/15 13:18:03 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_replace(char *s, size_t start, size_t end, char *in_s, int *hop)
{
	int		in_len;
	int		after_len;
	char	*res;

	if (!in_s)
		in_len = 0;
	else
		in_len = ft_strlen(in_s);
	after_len = ft_strlen(s + end);
	res = (char *)malloc(sizeof(char) * (start + in_len + after_len));
	if (!res)
		return (0);
	ft_strlcpy(res, s, start);
	if (in_s)
		ft_strlcpy(res + start - 1, in_s, in_len + 1);
	ft_strlcpy(res + start + in_len - 1, s + end, after_len + 1);
	if (hop)
		*hop = *hop + in_len - end + start - 2;
	return (res);	
}

char	*replace_env(char *s, size_t start, size_t end, int *hop)
{
	char	*env;
	char	*res;

	env = str_cut(s, start, end);
	if (!env)
		return (0);
	res = str_replace(s, start, end, getenv(env), hop);
	if (!res)
	{
		free (env);
		return (0);
	}
	free (env);
	return (res);
}

void	check_quotes(char *s, int i, int (*ebqd)[4])
{
	if (s[i] == '\'' && !(*ebqd)[2] && !(*ebqd)[3])
		(*ebqd)[2] = 1;
	else if (s[i] == '\'' && (*ebqd)[2] && !(*ebqd)[3])
		(*ebqd)[2] = 0;
	if (s[i] == '"' && !(*ebqd)[3] && !(*ebqd)[2])
		(*ebqd)[3] = 1;
	else if (s[i] == '"' && (*ebqd)[3] && !(*ebqd)[2])
		(*ebqd)[3] = 0;
	(*ebqd)[1] = is_backslash(s, i);
}

char	*handle_env(int (*ebqd)[4], char **s, int *i)
{
	char	*buf;

	(*ebqd)[0] = *i + 1;
	while (ft_isalnum((*s)[++*i]) || (*s)[*i] == '_')
		;
	buf = replace_env((*s), (*ebqd)[0], *i, i);
	free(*s);
	if (!buf)
		return (0);
	return (buf);
}

char	*resolve_env(const char *s)
{
	int		i;
	int		ebqd[4];
	char	*res;

	i = -1;
	ebqd[1] = 0;
	ebqd[2] = 0;
	ebqd[3] = 0;
	res = ft_strdup(s);
	if (!res)
		return (0);
	while (res && res[++i])
	{
		check_quotes(res, i, &ebqd);
		if (res[i] == '$' && res[i + 1] != '?' && !ebqd[1] && !ebqd[2])
		{
			res = handle_env(&ebqd, &res, &i);
			if (!res)
				return (0);
		}
	}
	return (res);
}
