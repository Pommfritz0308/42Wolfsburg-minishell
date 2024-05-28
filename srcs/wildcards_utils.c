/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:41:23 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/27 12:32:42 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*tab_to_str(char **arr)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = ft_strdup(arr[i]);
	i++;
	while (arr[i])
	{
		tmp = ft_strjoin(ret, " ");
		free(ret);
		ret = ft_strjoin(tmp, arr[i]);
		free(tmp);
		i++;
	}
	return (ret);
}

char	**add_row(char **arr, char *str)
{
	char	**new;
	int		i;

	i = 0;
	new = ft_calloc(ft_count_rows(arr) + 2, sizeof(char *));
	while (arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		free(arr[i]);
		i++;
	}
	free(arr);
	new[ft_count_rows(new)] = ft_strdup(str);
	return (new);
}

char	**sort_objs(char **old_arr, char *new_str)
{
	int		i;
	int		j;
	char	**new;
	char	*buff;
	int		n;

	i = -1;
	if (!old_arr)
		return (handle_empty_arr(new_str));
	new = add_row(old_arr, new_str);
	while (++i < ft_count_rows(new))
	{
		j = i;
		while (++j < ft_count_rows(new))
		{
			n = ft_strlen(new[i]);
			if (ft_strncmp(new[i], new[j], n) > 0)
			{
				buff = new[i];
				new[i] = new[j];
				new[j] = buff;
			}
		}
	}
	return (new);
}

char	**handle_empty_arr(char *new_str)
{
	char	**new;

	new = ft_calloc(2, sizeof(char *));
	new[0] = ft_strdup(new_str);
	return (new);
}

int	rev_search_str(char *dir, char *wild)
{
	int	i;
	int	j;

	i = ft_strlen(dir);
	j = ft_strlen(wild);
	while (wild[j] != '*' && i >= 0)
	{
		if (wild[j] != dir[i])
			return (false);
		j--;
		i--;
	}
	if (wild[j] == '*')
		return (true);
	return (false);
}
