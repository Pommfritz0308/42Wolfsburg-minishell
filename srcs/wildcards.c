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
			if (check_wildcard(dir->d_name, wildcard))
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
