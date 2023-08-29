#include <unistd.h>
#include <readline.h>

int	parse()
{
	if ("exit")
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
	clean_everything();
}
