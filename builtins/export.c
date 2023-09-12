#include "../minishell.h"
#include "../errnu.h"

void	print_export_helper(t_env *data)
{
	int		i;
	char	**pair;

	i = 0;
	while (data->temp_arr[i])
	{
		pair = identifier_value_pair(data->temp_arr[i]);
		if (pair[1])
			printf("declare -x %s=\"%s\"\n", pair[0], pair[1]);
		else
			printf("declare -x %s\n", pair[0]);
		ft_free_array(pair);
		i++;
	}
}

void	print_export(t_env *data)
{
	int		i;
	int		j;

	i = -1;
	data->temp_arr = ft_2d_array_cpy(data->env);
	while (++i < data->env_size)
	{
		j = i + 1;
		while (j < data->env_size)
		{
			data->n = ft_find_pos(data->temp_arr[i], '=');
			if (data->n == -1)
				data->n = ft_strlen(data->temp_arr[i]);
			if (ft_strncmp(data->temp_arr[i], data->temp_arr[j], data->n) > 0)
			{
				data->temp = data->temp_arr[i];
				data->temp_arr[i] = data->temp_arr[j];
				data->temp_arr[j] = data->temp;
			}
			j++;
		}
	}
	print_export_helper(data);
	ft_free_array(data->temp_arr);
}

void	ch_env(t_env *data, int i, char *arg, char **pair)
{
	if (!pair[1] || data->env == NULL)
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
	ch_env(data, i, arg, temp);
	ft_free_array(temp);
	return ;
}

int	ft_export(t_env *data, char *arg)
{
	char	**temp;
	int		i;

	if (arg)
	{
		i = -1;
		data->flag = 0;
		temp = identifier_value_pair(arg);
		if (!check_identifier(temp))
			return (EXIT_FAILURE);
		else
			ft_export_helper(data, temp, i, arg);
	}
	else
		print_export(data);
	return (EXIT_SUCCESS);
}
