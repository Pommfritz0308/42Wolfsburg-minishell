#include "minishell.h"

char	*curr_dir(char *start, char *end)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(".");
	start = end;
	printf("Curr dir\n");
	if (d)
	{
		dir = readdir(d);
		while (dir)
		{
    		printf("%s\n", dir->d_name);
			dir = readdir(d);
    	}
	}
    closedir(d);
	return (0);
}

char	*handle_wildcard(int (*ebqd)[4], char **s, int *i)
{
	int	start;

	start = *i;
	curr_dir(0, 0);
	(*ebqd)[0] = *i;
	return (*s);
}

char	*resolve_wildcards(char *s)
{
	int		i;
	int		ebqd[4];
	char	*res;

	i = -1;
	ebqd[1] = 0;
	ebqd[2] = 0;
	ebqd[3] = 0;
	res = ft_strdup(s);
	if (!res)
		return (0);
	while (res && res[++i])
	{
		check_quotes(res, i, &ebqd);
		if (res[i] == '*' && !ebqd[1] && !ebqd[2] && !ebqd[3])
		{
			res = handle_wildcard(&ebqd, &res, &i);
			if (!res)
				return (0);
		}
	}
	return (res);
}