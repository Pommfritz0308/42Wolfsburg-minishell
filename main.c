#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

int	parse(char *prompt)
{
	if (!ft_strncmp(prompt, "exit", 4))
		return (0);
	return (1);
}

int	main(void)
{
	char *prompt;

	while (1)
	{
		prompt = readline("minishell$ ");
		if (!parse(prompt))
			break ;
	}
}
