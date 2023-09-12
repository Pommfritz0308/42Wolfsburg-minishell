/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:49:08 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/12 10:30:15 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *s, int *i)
{
	int		env_len;
	char	*env;
	char	*val;

	env_len = 0;
	while (ft_isalnum(s[*i + ++env_len]))
		;
	env = (char *)malloc(sizeof(char) * env_len);
	if (!env)
		return (0);
	ft_strlcpy(env, s + *i + 1, env_len);
	env[env_len - 1] = 0;
	val = getenv(env);
	free(env);
	*i += env_len - 1;
	return (val);
}

int	hop_over_env(char *s, int *i)
{
	char	*val;
	int		res;

	val = get_env(s, i);
	res = 0;
	if (val)
		res = ft_strlen(val);
	return (res);
}

int	calc_len(char *s)
{
	int	len;
	int	i;

	len = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '$' && ft_isalnum(s[i + 1]))
			len += hop_over_env(s, &i);
		else
			len++;
	}
	return (len);
}

int		not_backslash(char *s, int pos)
{
	int	backslashes;

	if (!pos)
		return (1);
	backslashes = 0;
	while (--pos && s[pos] == '\\')
		backslashes++;
	if (backslashes % 2 == 0)
		return (1);
	return (0);
}

void	resolve_env_helper(char *s, char **res, char *val, int (*ijqd)[4])
{
	while (s && s[++(*ijqd)[0]])
	{
		if (s[(*ijqd)[0]] == '\'' && !(*ijqd)[3])
		{
			if ((*ijqd)[2])
				(*ijqd)[2] = 0;
			else
				(*ijqd)[2] = 1;
		}
		else if (s[(*ijqd)[0]] == '\"' && !(*ijqd)[2])
		{
			if ((*ijqd)[3])
				(*ijqd)[3] = 0;
			else
				(*ijqd)[3] = 1;
		}
		else if (!(*ijqd)[2] && s[(*ijqd)[0]] == '$' && ft_isalnum(s[(*ijqd)[0] + 1])
			&& not_backslash(s, (*ijqd)[0]))
		{
			val = get_env(s, &(*ijqd)[0]);
			if (val)
			{
				ft_strlcpy(*res + (*ijqd)[1], val, ft_strlen(val) + 1);
				(*ijqd)[1] += ft_strlen(val);
			}
		}
		else
			(*res)[(*ijqd)[1]++] = s[(*ijqd)[0]];
	}
	(*res)[(*ijqd)[1]] = 0;
}

char	*resolve_env(char *s)
{
	int		ijqd[4];
	char	*res;
	char	*val;

	res = (char *)malloc(sizeof(char) * (calc_len(s) + 1));
	if (!res)
		return (0);
	ijqd[0] = -1;
	ijqd[1] = 0;
	ijqd[2] = 0;
	ijqd[3] = 0;
	val = 0;
	resolve_env_helper(s, &res, val, &ijqd);
	return (res);
}
