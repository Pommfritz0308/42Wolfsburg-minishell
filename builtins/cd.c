#include "../minishell.h"
#include "../errnu.h"

int	cd(char *arg)
{
	char	*pwd;

	pwd = NULL;
	if (!arg | !arg[0])
		return (EXIT_SUCCESS);
	if (chdir(arg))
	{
		ft_perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
