/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:34:29 by fbohling          #+#    #+#             */
/*   Updated: 2023/08/31 14:39:51 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy(const char *s, char *arr, size_t start, size_t count)
{
	size_t	i;
	size_t	j;

	i = start;
	j = 0;
	while (i < start + count)
	{
		arr[j] = s[i];
		i++;
		j++;
	}
	arr[j] = '\0';
}

char	**fill_arr(t_split2 *data)
{
	int	i;
	int	y;

	i = 0;
	y = -1;
	data->arr = malloc((data->count + 1) * sizeof(char *));
	while (++y < data->count)
	{
		while (i != )
	}
}

int	indexing_matches(t_split2 *data)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	data->matches = malloc(2 * (data->count - 1) * sizeof(int));
	while (data->s1[i])
	{
		if (!strncmp(data->s1 + i, data->s2, data->s2_len))
		{
			if (flag == 0)
			{
				*(data->matches) = i;
				data->matches++;
			}
			i += data->s2_len;
			flag = -1;
		}
		else
		{
			if (flag == -1)
			{
				*(data->matches) = i;
				data->matches++;
			}
			i++;
			flag = 0;
		}
	}
	return (data->count);
}

int	substr_numb(t_split2 *data)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	data->count = 1;
	while (data->s1[i])
	{
		if (!ft_strncmp_2(data->s1 + i, data->s2, data->s2_len))
		{
			if (flag == 0 && i != 0 && i != data->s1_len - data->s2_len)
				data->count++;
			i += data->s2_len;
			flag = -1;
		}
		else
		{
			i++;
			flag = 0;
		}
	}
	return (data->count);
}

int	main(int argc, char *argv[])
{
	t_split2	data;

	data.s1 = argv[1];
	data.s2 = argv[2];
	data.s1_len = strlen(argv[1]);
	data.s2_len = strlen(argv[2]);
	// printf("Count %i\n", count_matches(&data));
	printf("Count %i\n", substr_numb(&data));
	indexing_matches(&data);
}
