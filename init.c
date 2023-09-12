#include "minishell.h"

void	print_asciiart(void)
{
	printf("\e[0;34m");
	printf("\n █▄ ▄█ █ █▄ █ █ ▄▀▀ █▄█ ██▀ █   █  ");
	printf("\n █ ▀ █ █ █ ▀█ █ ▄██ █ █ █▄▄ █▄▄ █▄▄\n\n");
	printf("\e[0m");
}

t_env	init_env(char **env)
{
	t_env	new;

	env_cpy(&new, env);
	return (new);
}

void	init_settings(void)
{
	int		fd;
	char	*home;
	char	*path;
	char	*inputrc;

	print_asciiart();
	home = getenv("HOME");
	if (!home || !*home)
		return ;
	path = ft_strjoin(home, MINISHELLRC);
	if (access(path, 0) == 0)
		return ;
	fd = open(path, O_WRONLY | O_CREAT, 0000644);
	write(fd, "set colored-stats on\n", 22);
	write(fd, "set enable-bracketed-paste off\n", 32);
	inputrc = getenv("INPUTRC");
	if (!inputrc || !*inputrc)
	{
		// We need to change it to our env builtin: setenv is forbidden function
		setenv("INPUTRC", path, 1);
	}
	close(fd);
	free(path);
}
