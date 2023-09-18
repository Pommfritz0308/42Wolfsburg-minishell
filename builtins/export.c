#include "../minishell.h"
#include "../errnu.h"

void	ch_env(t_env *data, int i, char *arg)
{
	if (data->env == NULL)
		return ;
	else if (data->flag == 1)
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

bool	check_identifier(char **arg, char *str)
{
	int	i;

	i = -1;
	if (!arg[0][0] || !arg[0])
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("\': not a valid identifier", 2);
		ft_free_array(arg);
		return (false);
	}
	while (arg[0][++i])
	{
		if ((!ft_isalpha(arg[0][i])
			&& arg[0][i] != '_') || !ft_isascii(arg[0][i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putendl_fd("\': not a valid identifier", 2);
			ft_free_array(arg);
			return (false);
		}
	}
	return (true);
}

void	ft_export_helper(t_env *data, char **temp, int i, char *arg)
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
	return ;
}

int	ft_export(t_env *data, char **args)
{
	char	**temp;
	int		i;

	i = 1;
	if (!args[i])
	{
		print_export(data);
		return (EXIT_SUCCESS);
	}
	while (args[i])
	{
		data->flag = 0;
		temp = identifier_value_pair(args[i]);
		if (check_identifier(temp, args[i]))
			ft_export_helper(data, temp, i, args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
