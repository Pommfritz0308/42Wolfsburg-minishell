#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_perror("pwd", 0, 0);
		return (EXIT_FAILURE);
	}
	else
		printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
