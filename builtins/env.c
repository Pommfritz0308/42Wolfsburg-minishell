#include "../minishell.h"
#include "../errnu.h"

int	ft_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strchr(envp[i], '='))
			printf("%s\n", envp[i]);
	}
	return (EXIT_SUCCESS);
}
