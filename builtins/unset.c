#include "../minishell.h"
#include "../errnu.h"

int	ft_unset(t_env *env, char **args)
{
	int	i;

	i = -1;
	if (!args || !args[0])
		return (EXIT_SUCCESS);
	while (args[i++])
	{
		handle_options(env, args[i]);
		ft_unset_helper(env, args, i);
	}
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
	int		j;
	char	**new_env;

	j = 0;
	i = -1;
	new_env = ft_calloc(env->env_size + 1, sizeof(char *));
	while (env->env[++i] != NULL)
	{
		if (i != pos)
		{
			new_env[j] = ft_strdup(env->env[i]);
			if (!new_env[j])
			{
				while (j-- > 0)
					free(new_env[j - 1]);
				return (free(new_env), NULL);
			}
			j++;
		}
	}
	new_env[j] = NULL;
	i = -1;
	while (env->env[++i] != NULL)
		free(env->env[i]);
	return (free(env->env), new_env);
}

int	handle_options(t_env *env, char **args)
{
	int	opt_flag;

	opt_flag = 0;
	if (opt )
}
