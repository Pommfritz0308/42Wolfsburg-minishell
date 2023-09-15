#include "../minishell.h"
#include "../errnu.h"

int	ft_echo(char **arg)
{
	if (!arg || !arg[1])
		printf("\n");
	else if (!ft_strncmp(arg[1], "-n", ft_strlen("-n")))
	{
		if (!arg[2])
			return (EXIT_SUCCESS);
		else
			print_args(arg, 2);
	}
	else
	{
		print_args(arg, 1);
		printf("\n");
	}
	return (EXIT_SUCCESS);
}

void	print_args(char **arr, int i)
{
	printf("%s", arr[i]);
	while (arr[++i])
		printf(" %s", arr[i]);
}
