/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:49:08 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/20 16:57:07 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_env(char *s, size_t start, size_t end, int *hop)
{
	char	*env;
	char	*res;
	char	*val;
	int		val_len;

	env = str_cut(s, start, end);
	if (!env)
		return (0);
	val = getenv(env);
	res = str_replace(s, start, end, val);
	if (!res)
	{
		free (env);
		return (0);
	}
	free (env);
	if (!val)
		val_len = 0;
	else
		val_len = ft_strlen(val);
	if (hop)
		*hop = *hop + val_len - end + start - 2;
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

char	*handle_exit_code(char **s, int *i, int prev_exit_code)
{
	char	*buf;
	char	*exit_code;

	exit_code = ft_itoa(prev_exit_code);
	if (!exit_code)
		return (0);
	buf = str_replace(*s, *i + 1, *i + 2, exit_code);
	free(*s);
	free(exit_code);
	*i += 1;
	if (!buf)
		return (0);
	return (buf);
}

char	*handle_home(char **s, int *i)
{
	char	*buf;

	buf = str_replace(*s, *i + 1, *i + 1, getenv("HOME"));
	free(*s);
	if (!buf)
		return (0);
	return (buf);
}


char	*resolve_env(const char *s, int prev_exit_code)
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
		if (res[i] == '$' && res[i + 1] != '?' && !ebqd[1] && !ebqd[2]
			&& (ft_isalnum(res[i + 1]) || res[i + 1] == '_')
		)
		{
			res = handle_env(&ebqd, &res, &i);
			if (!res)
				return (0);
		}
		else if (res[i] == '$' && res[i + 1] == '?' && !ebqd[1] && !ebqd[2])
		{
			res = handle_exit_code(&res, &i, prev_exit_code);
			if (!res)
				return (0);
		}
		else if (res[i] == '~' && !ebqd[1] && !ebqd[2] && !ebqd[3])
		{
			res = handle_home(&res, &i);
			if (!res)
				return (0);
		}
	}
	return (res);
}
