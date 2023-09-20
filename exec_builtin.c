#include "minishell.h"

int	exec_builtin(char **args, t_env *env)
{
	if (!ft_strncmp(args[0], "export", 7))
		return (ft_export(env, args));
	else if (!ft_strncmp(args[0], "pwd", 4))
		return (ft_pwd());
	else if (!ft_strncmp(args[0], "env", 4))
		return (ft_env(env->env));
	else if (!ft_strncmp(args[0], "cd", 3))
		return (ft_cd(env, args[1]));
	else if (!ft_strncmp(args[0], "unset", 6))
		return (ft_unset(env, args));
	else if (!ft_strncmp(args[0], "echo", 5))
		return (ft_echo(args));
	else if (!ft_strncmp(args[0], "$?", 3))
	{
		printf("minishell: %d: %s\n",
			WEXITSTATUS(env->prev_exit_code), ft_strerror());
		return (EXIT_SUCCESS);
	}
	else if (!ft_strncmp(args[0], "exit", 5))
	{
		exit(EXIT_SUCCESS);
		kill(0, SIGUSR1);
		return (EXIT_SUCCESS);
	}
	return (-1);
}
