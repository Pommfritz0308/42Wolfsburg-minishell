#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	exec_builtin(char **args, t_env *env, int fd_in, int fd_out, t_tree *tree)
{
	int	out_tmp;
	int	in_tmp;
	int	exit_code;

	exit_code = -1;
	if (!is_builtin(args[0]))
		return (exit_code);
	if (!ft_strncmp(args[0], "exit", 5))
	{
		kill(0, SIGUSR1);
		return (EXIT_SUCCESS);
	}
	in_tmp = dup(0);
	out_tmp = dup(1);
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	if (tree && tree->redirections)
		exit_code = redirections(tree->redirections);
	if (exit_code <= 0)
	{
		if (!ft_strncmp(args[0], "export", 7))
			exit_code = ft_export(env, args);
		else if (!ft_strncmp(args[0], "pwd", 4))
			exit_code = ft_pwd();
		else if (!ft_strncmp(args[0], "env", 4))
			exit_code = ft_env(env->env);
		else if (!ft_strncmp(args[0], "cd", 3))
			exit_code = ft_cd(env, args[1]);
		else if (!ft_strncmp(args[0], "unset", 6))
			exit_code = ft_unset(env, args);
		else if (!ft_strncmp(args[0], "echo", 5))
			exit_code = ft_echo(args);
	}
	if (exit_code > 0)
		exit_code = 258;
	dup2(in_tmp, 0);
	dup2(out_tmp, 1);
	close(out_tmp);
	close(in_tmp);
	return (exit_code);
}
