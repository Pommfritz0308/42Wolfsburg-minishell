#include "libft.h"

int	ft_find_pos(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			break ;
	}
	return (i);
}
