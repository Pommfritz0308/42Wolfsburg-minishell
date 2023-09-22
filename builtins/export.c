/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:58:00 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/22 17:58:03 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

bool	check_identifier(char **a, char *cmd, char *str)
{
	int		i;
	char	*err_msg;
	char	*tmp;

	i = -1;
	tmp = ft_strjoin("minishell: ", cmd);
	err_msg = ft_strjoin(tmp, ": `");
	free(tmp);
	tmp = ft_strjoin(str, "\': not a valid identifier");
	err_msg = ft_strjoin(err_msg, tmp);
	free(tmp);
	if (!a[0][0] || !a[0])
	{
		ft_putendl_fd(err_msg, 2);
		return (free(err_msg), false);
	}
	while (a[0][++i])
	{
		if ((!ft_isalnum(a[0][i]) && a[0][i] != '_') || !ft_isascii(a[0][i]))
		{
			ft_putendl_fd(err_msg, 2);
			return (free(err_msg), false);
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
		if (check_identifier(temp, "export", args[i]))
			ft_export_helper(data, temp, i, args[i]);
		else
			ft_free_array(temp);
		i++;
	}
	return (EXIT_SUCCESS);
}
