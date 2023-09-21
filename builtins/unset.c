#include "../includes/minishell.h"

int	ft_unset(t_env *env, char **args)
{
	int	i;

	i = 0;
	if (!args || !args[i])
		return (EXIT_SUCCESS);
	while (args[++i])
		ft_unset_helper(env, args, i);
	return (EXIT_SUCCESS);
}

void	ft_unset_helper(t_env *env, char **args, int i)
{
	int	j;

	if (check_identifier(&args[i], "unset", args[i]))
	{
		j = 0;
		while (env->env[j])
		{
			if (!ft_strncmp(env->env[j],
					args[i], ft_find_pos(env->env[j], '=')))
			{
				env->env_size--;
				env->env = delete_var(env, j);
			}
			j++;
		}
	}
}

char	**delete_var(t_env *env, int pos)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = ft_calloc(env->env_size + 1, sizeof(char *));
	delete_var_helper(env, i, pos, new_env);
	i = -1;
	while (env->env[++i] != NULL)
		free(env->env[i]);
	return (free(env->env), new_env);
}

void	delete_var_helper(t_env *env, int i, int pos, char **new_env)
{
	int	j;

	j = 0;
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
				return (free(new_env));
			}
			j++;
		}
	}
	new_env[j] = NULL;
}
