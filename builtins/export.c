#include "../minishell.h"
#include "../errnu.h"

void	ch_env(t_builtins *data, int i, char *arg)
{
	if (data->flag == 1)
	{
		free(data->env[i]);
		data->env[i] = ft_strdup(arg);
	}
	else
	{
		data->env_size++;
		data->env = realloc_env(data, data->env_size);
		data->env[data->env_size - 1] = ft_strdup(arg);
	}
}

char	**identifier_value_pair(char *arg)
{
	char	**pair;
	char	*eq_sign;

	eq_sign = ft_strchr(arg, '=');
	pair = calloc(3, sizeof(char *));
	pair[0] = ft_substr(arg, 0, eq_sign - arg);
	if (eq_sign)
		pair[1] = ft_substr(eq_sign, 1, ft_strlen(eq_sign));
	else
		pair[1] = NULL;
	pair[2] = NULL;
	return (pair);
}

bool	check_identifier(char **arg)
{
	int	i;

	i = -1;
	if (!arg[0][0] | !arg[0])
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putendl_fd("\': not a valid identifier", 2);
		ft_free_array(arg);
		return (false);
	}
	while (arg[0][++i])
	{
		if (!ft_isalpha(arg[0][i]) &&
			arg[0][i] != '_' && !ft_isascii(arg[0][i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(arg[0], 2);
			ft_putendl_fd("\': not a valid identifier", 2);
			ft_free_array(arg);
			return (false);
		}
	}
	return (true);
}

int	ft_export(t_builtins *data, char *arg)
{
	char	**temp;
	int		i;

	i = -1;
	data->flag = 0;
	if (!arg)
		print_export(data);
	temp = identifier_value_pair(arg);
	if (!check_identifier(temp))
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
		ch_env(data, i, arg);
		ft_free_array(temp);
	}
	return (EXIT_SUCCESS);
}

