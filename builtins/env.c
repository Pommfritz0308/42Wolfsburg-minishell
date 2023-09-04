#include "../minishell.h"
#include "../errnu.h"

void	env_(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}
