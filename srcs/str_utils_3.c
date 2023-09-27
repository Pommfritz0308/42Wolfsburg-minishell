/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:30:27 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/27 12:30:28 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*str_replace(char *s, size_t start, size_t end, char *in_s)
{
	int		in_len;
	int		after_len;
	char	*res;

	if (!in_s)
		in_len = 0;
	else
		in_len = ft_strlen(in_s);
	if (end >= ft_strlen(s))
		after_len = 1;
	else
		after_len = ft_strlen(s + end);
	res = (char *)ft_calloc(start + in_len + after_len, sizeof(char));
	if (!res)
		return (0);
	ft_strlcpy(res, s, start);
	if (in_s)
		ft_strlcpy(res + start - 1, in_s, in_len + 1);
	if (end < ft_strlen(s))
		ft_strlcpy(res + start + in_len - 1, s + end, after_len + 1);
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

void	add_line(char **full_input, char **line)
{
	char	*buf;

	buf = str_join(*full_input, *line, "");
	free(*line);
	free(*full_input);
	*full_input = buf;
	buf = str_join(*full_input, "\n", "");
	free(*full_input);
	*full_input = buf;
	*line = readline(HEREDOC_PROMPT);
}

int	tputs_putchar(int c)
{
	return (write(1, &c, 1));
}

char	*str_getenv(char *key, t_env *env)
{
	char	*buf;
	char	*val;

	buf = str_join(key, "=", "");
	if (!buf)
		return (0);
	val = retr_env_value(env, buf);
	free(buf);
	return (val);
}
