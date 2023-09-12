/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:16:48 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/12 14:17:37 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
