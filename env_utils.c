#include "minishell.h"
#include "errnu.h"

bool	env_cpy(t_builtins *data, char **envp)
{
	int			i;

	i = -1;
	data->env_size = 0;
	while (envp && envp[data->env_size])
		data->env_size++;
	data->env = ft_calloc(data->env_size + 1, sizeof(char *));
	if (!data->env)
		return (false);
	while (++i < data->env_size)
		data->env[i] = ft_strdup(envp[i]);
	return (true);
}
