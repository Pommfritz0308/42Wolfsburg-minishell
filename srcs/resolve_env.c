/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:49:08 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/26 14:34:20 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_env(int (*ebqd)[4], char **s, int *i, t_env *env)
{
	char	*buf;
	char	*in_s;

	(*ebqd)[0] = *i + 1;
	if (ft_isdigit((*s)[++*i]))
	{
		if ((*s)[*i] - '0' < env->ac)
			in_s = env->av[(*s)[*i] - '0'];
		else
			in_s = "";
		buf = str_replace(*s, (*ebqd)[0], *i + 1, in_s);
	}
	else
	{
		while (ft_isalnum((*s)[++*i]) || (*s)[*i] == '_')
			;
		buf = replace_env(*s, (*ebqd)[0], i, env);
	}
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

char	*handle_home(char **s, int *i, t_env *env)
{
	char	*buf;
	char	*home;

	home = str_getenv("HOME", env);
	if (!home)
		buf = str_replace(*s, *i + 1, *i + 1, getenv("HOME"));
	else
		buf = str_replace(*s, *i + 1, *i + 1, home);
	if (home)
		free(home);
	free(*s);
	if (!buf)
		return (0);
	return (buf);
}

int	check_tilda(char *res, int i, int ebqd[4])
{
	return (
		res[i] == '~' && !ebqd[1] && !ebqd[2] && !ebqd[3]
		&& (i == 0 || str_contains(res[i - 1], " \t"))
		&& (!res[i + 1] || str_contains(res[i + 1], " \t/"))
	);
}

char	*resolve_env(const char *s, t_env *env)
{
	int		i;
	int		ebqd[4];
	char	*res;

	i = -1;
	ebqd[1] = 0;
	ebqd[2] = 0;
	ebqd[3] = 0;
	res = ft_strdup(s);
	while (res && res[++i])
	{
		check_quotes(res, i, &ebqd);
		if (res[i] == '$' && res[i + 1] != '?' && !ebqd[1] && !ebqd[2]
			&& (ft_isalnum(res[i + 1]) || res[i + 1] == '_')
		)
			res = handle_env(&ebqd, &res, &i, env);
		else if (res[i] == '$' && res[i + 1] == '?' && !ebqd[1] && !ebqd[2])
			res = handle_exit_code(&res, &i, env->prev_exit_code);
		else if (check_tilda(res, i, ebqd))
			res = handle_home(&res, &i, env);
		else if (res[i] == '*' && !ebqd[1] && !ebqd[2] && !ebqd[3])
			res = handle_wildcard(&res, &i);
	}
	return (res);
}
