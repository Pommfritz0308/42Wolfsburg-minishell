#include "minishell.h"
#include "errnu.h"

int	env_cpy(t_builtins *data, char **envp)
{
	int			i;

	i = -1;
	data->env_size = 0;
	while (envp && envp[data->env_size])
		data->env_size++;
	data->env = ft_calloc(data->env_size + 1, sizeof(char *));
	if (!data->env)
		return (EXIT_FAILURE);
	while (++i < data->env_size)
		data->env[i] = ft_strdup(envp[i]);
	return (EXIT_SUCCESS);
}

char	**realloc_env(t_builtins *data, int size)
{
	char	**new_env;
	int		i;

	i = -1;
	new_env = ft_calloc(size + 1, sizeof(char *));
	while (data->env[++i])
	{
		new_env[i] = ft_strdup(data->env[i]);
		free(data->env[i]);
	}
	free(data->env);
	return (new_env);
}
