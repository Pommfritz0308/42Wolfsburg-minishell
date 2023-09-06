#include "../minishell.h"
#include "../errnu.h"

int	ft_export(t_builtins *data, char *arg)
{
	char	**temp;
	int		i;
	int		len;

	i = -1;
	data->flag = 0;
	temp = new_env(data, arg);
	if (!check_identifier(temp[0]))
		return (EXIT_FAILURE);
	else
	{
		while (data->env[++i])
		{
			if (!ft_strncmp(data->env[i],
					temp[0], ft_find_pos(data->env[i], '=')))
			{
				data->flag = 1;
				break ;
			}
		}
		ch_env(data, temp, i, arg);
		ft_free_array(temp);
	}
	return (EXIT_SUCCESS);
}

void	ch_env(t_builtins *data, char **pair, int i, char *arg)
{
	if (data->flag == 1)
	{
		free(data->env[i]);
		data->env[i] = ft_strdup(arg);
	}
	else
	{
		data->env_size++;
		realloc_env(data, data->env_size);
		data->env[data->env_size] = ft_strdup(arg);
	}
}

char	**identifier_value_pair(t_builtins *data, char *arg)
{
	char	**new_env;
	char	*eq_sign;
	int		i;

	eq_sign = ft_strchr(arg, '=');
	new_env = calloc(3, sizeof(char *));
	new_env[0] = ft_substr(arg, 0, eq_sign - arg);
	new_env[1] = ft_substr(eq_sign, 1, ft_strlen(eq_sign));
	new_env[2] = NULL;
	return (new_env);
}

bool	check_identifier(char *arg)
{
	int	i;

	i = -1;
	if (!arg[0] | !arg)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("\': not a valid identifier", 2);
		return (false);
	}
	while (arg[++i])
	{
		if (arg[i] == '_' | !ft_isalpha(arg[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(arg[0], 2);
			ft_putendl_fd("\': not a valid identifier", 2);
			return (false);
		}
	}
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	print_env(envp);
}
