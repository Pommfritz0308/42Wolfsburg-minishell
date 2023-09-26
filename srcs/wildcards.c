#include "../includes/minishell.h"

bool	check_dots(char *wild, char *file)
{
	if (wild[0] == '.')
		return (true);
	if (file[0] == '.')
		return (false);
	return (true);
}

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
	size_t	i;
	char	*temp;
	int		pos;
	int		len;

	i = 0;
	while (wild[i] == '*')
		i++;
	if (i == ft_strlen(wild))
		return (true);
	i = 0;
	temp = NULL;
	pos = 0;
	len = 0;
	if (wild[0] != '*')
	{
		while (dir[i] == wild[i])
			i++;
		if (wild[i] != '*')
			return (false);
		else
			return (check(wild + i, dir + i));
	}
	else
	{
		while (wild[i] == '*')
			i++;
		if (!ft_strchr(wild + i, '*'))
		{
			if (rev_search_str(dir, wild))
				return (true);
			else
				return (false);
		}
		else
		{
			temp = ft_substr(wild + i, 0, ft_find_pos(wild + 1, '*'));
			len = ft_strlen(temp);
			pos = ft_find_substr(dir, temp);
			if (pos == -1)
				return (free(temp), false);
			else
				return (free(temp), check(wild + (ft_find_pos(wild + 1, '*')
							+ 1), dir + (pos + len)));
		}

	}
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

char	**sort_objs(char **old_arr, char *new_str)
{
	int		i;
	int		j;
	char	**new;
	char	*buff;
	int		n;

	n = 0;
	i = -1;
	if (!old_arr)
	{
		new = ft_calloc(2, sizeof(char *));
		new[0] = ft_strdup(new_str);
		return (new);
	}
	new = add_row(old_arr, new_str);
	while (++i < ft_count_rows(new))
	{
		j = i + 1;
		while (j < ft_count_rows(new))
		{
			n = ft_strlen(new[i]);
			if (ft_strncmp(new[i], new[j], n) > 0)
			{
				buff = new[i];
				new[i] = new[j];
				new[j] = buff;
			}
			j++;
		}
	}
	return (new);
}

char **add_row(char **arr, char *str)
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
