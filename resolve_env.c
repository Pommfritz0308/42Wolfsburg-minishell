/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:49:08 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/14 20:01:11 by psimonen         ###   ########.fr       */
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

char	*str_cut(char *s, size_t start, size_t end)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (0);
	ft_strlcpy(res, s + start, end - start + 1);
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

int	not_backslash(char *s, int i)
{
	int	backslashes;

	backslashes = 0;
	while (--i >= 0 && s[i] == '\\')
		backslashes++;
	return (backslashes % 2);
}

char	*resolve_env(const char *s)
{
	int		i;
	int		ebqd[4];
	char	*res;
	char	*buf;

	i = -1;
	ebqd[1] = 0;
	ebqd[2] = 0;
	ebqd[3] = 0;
	res = ft_strdup(s);
	if (!res)
		return (0);
	while (res && res[++i])
	{
		if (res[i] == '\'' && !ebqd[2] && !ebqd[3])
			ebqd[2] = 1;
		else if (res[i] == '\'' && ebqd[2] && !ebqd[3])
			ebqd[2] = 0;
		if (res[i] == '"' && !ebqd[3] && !ebqd[2])
			ebqd[3] = 1;
		else if (res[i] == '"' && ebqd[3] && !ebqd[2])
			ebqd[3] = 0;
		ebqd[1] = not_backslash(res, i);
		if (res[i] == '$' && res[i + 1] != '?' && !ebqd[1] && !ebqd[2])
		{
			ebqd[0] = i + 1;
			while (ft_isalnum(res[++i]) || res[i] == '_')
				;
			buf = replace_env(res, ebqd[0], i, &i);
			free(res);
			if (!buf)
				return (0);
			res = buf;
		}
	}
	return (res);
}
