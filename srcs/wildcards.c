#include "../includes/minishell.h"

char	*dir_iteri(struct dirent *dir, DIR *d, char *wildcard)
{
	char	*res;
	char	*tmp;

	res = NULL;
	tmp = NULL;
	if (d)
	{
		dir = readdir(d);
		while (dir)
		{
			if (check(wildcard, dir->d_name))
			{
				tmp = ft_strjoin(res, dir->d_name);
				res = ft_strjoin(tmp, " ");
				free(tmp);
			}
			dir = readdir(d);
		}
	}
	return (res);
}

// bool	check_wildcard(char *dir, char *wildc)
// {
// 	int		i;
// 	char	**arr;


// 	i = 0;
// 	if (wildc[0] == '*' && !wildc[1])
// 		return (true);
// 	arr = ft_split(wildc, '*');
// 	if (wildc[i] == '*' && ft_find_substr(dir, arr[i]) == 0)
// 	{
// 		ft_free_array(arr);
// 		return (false);
// 	}
// 	while (arr[++i])
// 	{
// 		if (ft_find_substr(dir, arr[i]) == -1)
// 		{
// 			ft_free_array(arr);
// 			return (false);
// 		}
// 	}
// 	ft_free_array(arr);
// 	return (true);
// }

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
			temp = ft_substr(wild + i, 0, ft_find_pos(wild + 1, '*') - 1);
			len = ft_strlen(temp);
			pos = ft_find_substr(dir, temp);
			if (pos == -1)
				return (free(temp), false);
			else
				return (free(temp), check(wild + ft_find_pos(wild + 1, '*'), dir + (pos + len))); // continue at wild[i] == '*' & dir[i] == end of match
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
