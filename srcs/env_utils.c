#include "../includes/minishell.h"

int	env_cpy(t_env *data, char **envp)
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

char	**realloc_env(t_env *data, int size)
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

int	update_shlvl(t_env *env)
{
	char	*shlvl;
	char	*temp;
	int		i;

	i = 1;
	shlvl = NULL;
	temp = NULL;
	if (!retr_env_value(env, "SHLVL="))
		ft_export_cd(env, "SHLVL", "SHLVL=1");
	else
	{
		shlvl = retr_env_value(env, "SHLVL=");
		i += ft_atoi(shlvl);
		free(shlvl);
		shlvl = ft_itoa(i);
		temp = ft_strjoin("SHLVL=", shlvl);
		ft_export_cd(env, "SHLVL", temp);
		free(shlvl);
		free(temp);
	}
	return (EXIT_SUCCESS);
}
