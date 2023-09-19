#include "minishell.h"

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
		path = getcwd(0, 0);
	return (str_split(path, ':'));
}

char	*join_path(char	*s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
		i++;
	if (*s2 == '/' || (i && s1[i - 1] == '/'))
		return (str_join(s1, s2, ""));
	return (str_join(s1, s2, "/"));
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
				clean_tab(paths);
				return (exec_path);
			}
			free(exec_path);
		}
		clean_tab(paths);
	}
	if (exec && access(exec, 0) == 0 && str_contains('/', exec))
		return (exec);
	free(exec);
	ft_perror(exec, N_FOUND);
	return (0);
}
