#include "../includes/minishell.h"

char	*replace_env(char *s, size_t start, size_t end, int *hop, t_env *data)
{
	char	*env;
	char	*res;
	char	*val;
	char	*buf;
	int		val_len;

	env = str_cut(s, start, end);
	if (!env)
		return (0);
	buf = str_join(env, "=", "");
	val = retr_env_value(data, buf);
	free(buf);
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
	if (val)
		free(val);
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
