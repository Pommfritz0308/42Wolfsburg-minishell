#include "minishell.h"

int	exec_builtin(char *cmd, char **args, t_env *env)
{
	if (!ft_strncmp(cmd, "export", ft_strlen("export")))
		exit(ft_export(env, args));
	else if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		exit(ft_pwd());
	else if (!ft_strncmp(cmd, "env", ft_strlen("env")))
		exit(ft_env(env->env));
	//else if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
	//	ft_cd(env, args[1]);
	else if (!ft_strncmp(cmd, "$?", 2))
		printf("minishell: %d: %s\n", WEXITSTATUS(env->prev_exit_code), ft_strerror());
	else if (!ft_strncmp(cmd, "exit", 5))
		kill(0, SIGUSR1);
	return (0);
}
