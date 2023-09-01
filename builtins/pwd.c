#include "../minishell.h"

char	*pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0); // remember to free buff
	return (cwd);
}
