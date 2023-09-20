#include "../minishell.h"
#include "../errnu.h"

int	ft_unset(t_env *env, char **args)
{
	int	i;
	int	j;

	i = 0;
	if (!args || !args[i])
		return (EXIT_SUCCESS);
	while (args[i])
	{
		if (check_identifier(&args[i], "unset", args[i]))
		{
			j = 0;
			while (env->env[j])
			{
				if (!ft_strncmp(env->env[j],
						args[i], ft_find_pos(env->env[j], '=')))
					env->env = delete_var(env, j);
				j++;
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

char	**delete_var(t_env *env, int pos)
{
	int		i;
	int		j;
	char	**new_env;

	j = 0;
	i = -1;
	env->env_size--;
	new_env = ft_calloc(env->env_size + 1, sizeof(char *));
	while (env->env[++i] != NULL)
	{
		if (i != pos)
		{
			new_env[j] = ft_strdup(env->env[i]);
			if (!new_env[j])
			{
				while (j > 0)
				{
					free(new_env[j - 1]);
					j--;
				}
				free(new_env);
				return (NULL);
			}
			j++;
		}
	}
	new_env[j] = NULL;
	i = -1;
	while (env->env[++i] != NULL)
		free(env->env[i]);
	free(env->env);
	return (new_env);
}
