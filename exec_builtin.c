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

int	exec_builtin_helper(int exit_code, char **args, t_env *env)
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
	return (exit_code);
}

int	exit_helper(t_env *env, char **args)
{
	env->curr_exit_code = EXIT_SUCCESS;
	clean_tab(args);
	kill(0, SIGUSR1);
	return (env->curr_exit_code);
}

int	exec_builtin(t_env *env, int fd_in, int fd_out, t_tree *tree)
{
	int		oie[3];
	char	**args;

	oie[2] = -1;
	if (!is_builtin(tree->args->content))
		return (oie[2]);
	args = lst_to_tab(&(tree->args));
	if (!ft_strncmp(args[0], "exit", 5))
		return (exit_helper(env, args));
	oie[1] = dup(0);
	oie[0] = dup(1);
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	if (tree && tree->redirections)
		oie[2] = redirections(tree->redirections);
	if (oie[2] <= 0)
		oie[2] = exec_builtin_helper(oie[2], args, env);
	if (oie[2] > 0)
		oie[2] = 258;
	dup2(oie[1], 0);
	dup2(oie[0], 1);
	close(oie[0]);
	close(oie[1]);
	clean_tab(args);
	return (oie[2]);
}
