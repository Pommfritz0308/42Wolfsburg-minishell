#include "minishell.h"

int	exec_builtin(t_tree *node, t_env *env)
{
	char	**args;

	args = lst_to_tab(node->args);
	if (!ft_strncmp(args[0], "export", ft_strlen("export")))
		return(ft_export(env, args));
	else if (!ft_strncmp(args[0], "pwd", ft_strlen("pwd")))
		return(ft_pwd());
	else if (!ft_strncmp(args[0], "env", ft_strlen("env")))
		return(ft_env(env->env));
	//else if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
	//	ft_cd(env, args[1]);
	else if (!ft_strncmp(args[0], "$?", 2))
		printf("minishell: %d: %s\n", WEXITSTATUS(env->prev_exit_code), ft_strerror());
	else if (!ft_strncmp(args[0], "exit", 5))
		kill(0, SIGUSR1);
	return (-1);
}
