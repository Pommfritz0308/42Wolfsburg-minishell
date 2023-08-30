/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:49:08 by psimonen          #+#    #+#             */
/*   Updated: 2023/08/30 14:55:00 by psimonen         ###   ########.fr       */
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

void	resolve_env_helper(char *s, char **res, char *val, int (*ijq)[3])
{
	while (s && s[++(*ijq)[0]])
	{
		if (s[(*ijq)[0]] == '\'')
		{
			if ((*ijq)[2])
				(*ijq)[2] = 0;
			else
				(*ijq)[2] = 1;
		}
		if (!(*ijq)[2] && s[(*ijq)[0]] == '$' && ft_isalnum(s[(*ijq)[0] + 1]))
		{
			val = get_env(s, &(*ijq)[0]);
			if (val)
			{
				ft_strlcpy(*res + (*ijq)[1], val, ft_strlen(val) + 1);
				(*ijq)[1] += ft_strlen(val);
			}
		}
		else
			(*res)[(*ijq)[1]++] = s[(*ijq)[0]];
	}
	(*res)[(*ijq)[1]] = 0;
}

char	*resolve_env(char *s)
{
	int		ijq[3];
	char	*res;
	char	*val;

	res = (char *)malloc(sizeof(char) * (calc_len(s) + 1));
	if (!res)
		return (0);
	ijq[0] = -1;
	ijq[1] = 0;
	ijq[2] = 0;
	val = 0;
	resolve_env_helper(s, &res, val, &ijq);
	return (res);
}
