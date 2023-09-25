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
