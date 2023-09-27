/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:30:08 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/27 12:30:09 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*replace_env(char *s, size_t start, int *end, t_env *data)
{
	char	*env;
	char	*res;
	char	*val;
	int		val_len;

	env = str_cut(s, start, *end);
	if (!env)
		return (0);
	val = str_getenv(env, data);
	res = str_replace(s, start, *end, val);
	free (env);
	if (!val)
		val_len = 0;
	else
		val_len = ft_strlen(val);
	if (val)
		free(val);
	if (end)
		*end = val_len + start - 2;
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

void	find_ends(int *start, int *end, char *s)
{
	while (*start >= 0 && (is_backslash(s, *start)
			|| !str_contains(s[*start], " \t|&()'\"\n")))
		(*start)--;
	(*start)++;
	while (s[*end] && (is_backslash(s, *end)
			|| !str_contains(s[*end], " \t|&()'\"\n")))
		(*end)++;
	(*end)--;
}

char	*handle_wildcard(char **s, int *i)
{
	char	*buf;
	char	*resolved;
	int		start;
	int		end;

	start = *i - 1;
	end = *i + 1;
	find_ends(&start, &end, *s);
	buf = str_slice(*s, start, end);
	resolved = resolve_wildcards(buf);
	*i = end;
	if (!resolved)
		return (free(buf), *s);
	free(buf);
	buf = str_replace(*s, start + 1, end + 1, resolved);
	*i = *i - end + start + ft_strlen(resolved);
	free(resolved);
	free(*s);
	return (buf);
}
