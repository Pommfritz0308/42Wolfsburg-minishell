#include "../minishell.h"
#include "../errnu.h"

int	main(int argc, char **argv, char **envp)
{
	print_env(envp);
}