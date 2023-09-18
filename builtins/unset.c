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
		if (check_identifier(args[i], args[i]))
		{
			j = -1;
			while (env->env[++j])
			{
				if (!ft_strncmp(env->env[j],
						args[i], ft_find_pos(env->env[j], '=')))
					env->env = delete_var(env, env->env[j], j);
			}
		}
	}
	return (EXIT_SUCCESS);
}

char	**delete_var(t_env *env, char *del, int pos)
{
	int		i;
	char	**new_env;

	i = -1;
	free(del);
	env->env_size--;
	new_env = ft_calloc(env->env_size + 1, sizeof(char *));
	while (env->env[++i])
	{
		if (i != pos)
		{
			new_env[i] = ft_strdup(env->env[i]);
			free(env->env[i]);
		}
	}
	free(env->env);
	return (new_env);
}