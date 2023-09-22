#include "../includes/minishell.h"

void	print_asciiart(void)
{
	printf("\e[0;34m");
	printf("\n █▄ ▄█ █ █▄ █ █ ▄▀▀ █▄█ ██▀ █   █  ");
	printf("\n █ ▀ █ █ █ ▀█ █ ▄██ █ █ █▄▄ █▄▄ █▄▄\n\n");
	printf("\e[0m");
}

t_env	init_env(int ac, char **av, char **env)
{
	t_env	new;

	env_cpy(&new, env);
	new.prev_exit_code = EXIT_SUCCESS;
	new.curr_exit_code = EXIT_SUCCESS;
	new.ac = ac;
	new.av = av;
	return (new);
}

void	init_settings(void)
{
	int		fd;
	char	*home;
	char	*path;

	//print_asciiart();
	home = getenv("HOME");
	if (!home || !*home)
		return ;
	path = ft_strjoin(home, MINISHELLRC);
	if (access(path, 0) == 0)
	{
		free(path);
		return ;
	}
	fd = open(path, O_WRONLY | O_CREAT, 0000644);
	write(fd, "set colored-stats on\n", 22);
	write(fd, "set enable-bracketed-paste off\n", 32);
	close(fd);
	free(path);
}
