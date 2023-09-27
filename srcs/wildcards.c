/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:12:23 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/27 11:17:43 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dir_iteri(struct dirent *dir, DIR *d, char *wildcard)
{
	char	**arr;
	char	*res;

	res = NULL;
	arr = NULL;
	if (d)
	{
		dir = readdir(d);
		while (dir)
		{
			if (check_dots(wildcard, dir->d_name)
				&& check(wildcard, dir->d_name))
			{
				arr = sort_objs(arr, dir->d_name);
			}
			dir = readdir(d);
		}
		if (arr)
		{
			res = tab_to_str(arr);
			clean_tab(arr);
		}
	}
	return (res);
}

char	*resolve_wildcards(char *wildcard)
{
	char			*res;
	DIR				*d;
	struct dirent	dir;

	res = NULL;
	d = opendir(".");
	res = dir_iteri(&dir, d, wildcard);
	closedir(d);
	return (res);
}

int	check(char *wild, char *dir)
{
	t_wcd	d;

	d.temp = NULL;
	d.pos = 0;
	d.len = 0;
	if (no_pattern(wild))
		return (true);
	d.i = 0;
	if (wild[0] != '*')
	{
		while (dir[d.i] == wild[d.i])
			d.i++;
		if (wild[d.i] != '*')
			return (false);
		else
			return (check(wild + d.i, dir + d.i));
	}
	else
	{
		if (check_helper(wild, dir, &d) == -1)
			return (check(wild + (ft_find_pos(wild + 1, '*')
						+ 1), dir + (d.pos + d.len)));
		else
			return (d.ret);
	}
}

int	check_helper(char *wild, char *dir, t_wcd *d)
{
	while (wild[d->i] == '*')
		d->i++;
	if (!ft_strchr(wild + d->i, '*'))
	{
		d->ret = pattern_at_end(dir, wild);
		return (d->ret);
	}
	else
	{
		d->temp = ft_substr(wild + d->i, 0, ft_find_pos(wild + 1, '*'));
		d->len = ft_strlen(d->temp);
		d->pos = ft_find_substr(dir, d->temp);
		if (d->pos == -1)
		{
			d->ret = 0;
			return (free(d->temp), false);
		}
		else
			return (free(d->temp), -1);
	}
}
