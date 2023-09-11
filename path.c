#include "minishell.h"

char	*str_unescape(char *s)
{
	int		len;
	int		i;
	char	*res;

	len = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\\' && str_contains(s[i + 1], "\"\'\\"))
			continue ;
		len++;
	}
	res = (char *)ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (0);
	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] == '\\' && str_contains(s[i + 1], "\"\'\\"))
			continue ;
		res[len] = s[i];
		len++;
	}
	return (res);
}

void	free_tab(char **t)
{
	int	i;

	i = -1;
	while (t[++i])
		free(t[i]);
	free(t);
}

static int	add_word(const char *s, char **dest, char c)
{
	int	len;
	int	i;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	*dest = (char *)ft_calloc(len + 1, sizeof(char));
	if (!(*dest))
		return (-1);
	i = -1;
	while (++i < len)
		(*dest)[i] = s[i];
	return (1);
}

static int	count_words(const char *s, char c, char **res)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			if (res && add_word(s + i, res + len, c) == -1)
				return (-1);
			len++;
			while (s[i] && s[i] != c)
				i++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (len);
}

char	**f_split(char const *s, char c)
{
	int		count;
	char	**res;

	if (!s)
		return (0);
	count = count_words(s, c, 0);
	res = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!res)
		return (0);
	if (count_words(s, c, res) == -1)
	{
		count = -1;
		while (res[++count])
			free(res[count]);
		free(res);
		return (0);
	}
	return (res);
}

char	**find_path(char **env)
{
	char	*path;

	path = 0;
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
			path = *env + 5;
		env++;
	}
	if (!path)
		path = "/usr/bin";
	return (f_split(path, ':'));
}

char	*f_strjoin(char const *s1, char const *s2, char *sep)
{
	char	*res;
	int		s1_len;
	int		s2_len;
	int		sep_len;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	sep_len = ft_strlen(sep);
	res = (char *)ft_calloc(s1_len + s2_len + sep_len + 1, sizeof(char));
	if (!res)
		return (0);
	res = ft_memcpy(res, s1, s1_len);
	ft_memcpy(res + s1_len, sep, sep_len);
	ft_memcpy(res + s1_len + sep_len, s2, s2_len);
	return (res);
}

char	*join_path(char	*s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
		i++;
	if (*s2 == '/' || (i && s1[i - 1] == '/'))
		return (f_strjoin(s1, s2, ""));
	return (f_strjoin(s1, s2, "/"));
}

char	*path_to_exec(char *exec, char **env)
{
	char	**paths;
	char	**buf;
	char	*exec_path;

	paths = find_path(env);
	if (paths)
	{
		buf = paths - 1;
		while (*(++buf))
		{
			exec_path = join_path(*buf, exec);
			if (access(exec_path, 0) == 0)
			{
				free_tab(paths);
				return (exec_path);
			}
			free(exec_path);
		}
		free_tab(paths);
	}
	exec = str_unescape(exec);
	if (exec && access(exec, 0) == 0 && str_contains('/', exec))
		return (exec);
	free(exec);
	return (0);
}