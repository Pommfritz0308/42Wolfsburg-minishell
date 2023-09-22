#include "../includes/minishell.h"

void	set_iow(int fd_in, int fd_out, int wait_flag, int (*iow)[3])
{
	(*iow)[0] = fd_in;
	(*iow)[1] = fd_out;
	(*iow)[2] = wait_flag;
}

int	only_redirections(int fd_in, int fd_out, t_tree *tree)
{
	int	pid;
	int	exit_code;

	pid = fork();
	if (!pid)
	{
		if (dup2(fd_in, 0) < 0 || dup2(fd_out, 1) < 0)
			return (0);
		exit_code = redirections(tree->redirections);
		exit(exit_code);
	}
	return (pid);
}

int	exec_cmd(t_tree *tree, int fd_in, int fd_out, t_env *env)
{
	int		pid;
	int		exit_code;
	char	*full_cmd;

	pid = fork();
	if (!pid)
	{
		if (dup2(fd_in, 0) < 0 || dup2(fd_out, 1) < 0)
			return (0);
		full_cmd = path_to_exec(tree->args->content, env);
		if (!full_cmd)
			exit(env->curr_exit_code);
		if (tree->redirections)
		{
			exit_code = redirections(tree->redirections);
			if (exit_code)
				exit(exit_code);
		}
		if (execve(full_cmd, lst_to_tab(&(tree->args)), env->env) < 0)
			exit (127);
	}
	return (pid);
}

int	exec_pipe(t_tree *tree, t_env *env, int iow[3])
{
	int		exit_code;
	int		iow_c[3];
	int		fd[2];

	exit_code = 258;
	if (!tree->left || !tree->right)
		return (ft_perror(0, SY_PIPE, exit_code));
	if (pipe(fd) < 0)
		return (ft_perror(0, 0, EXIT_FAILURE));
	set_iow(iow[0], fd[1], WNOHANG, &iow_c);
	exec_recursive(tree->left, env, iow_c);
	close(fd[1]);
	set_iow(fd[0], iow[1], iow[2], &iow_c);
	exit_code = exec_recursive(tree->right, env, iow_c);
	return (exit_code);
}

int	exec_cond(t_tree *tree, t_env *env, int iow[3])
{
	int	exit_code;
	int	iow_c[3];

	exit_code = 258;
	if (!tree->right || !tree->left)
		return (ft_perror(0, COND_ERR, exit_code));
	set_iow(iow[0], iow[1], 0, &iow_c);
	exit_code = exec_recursive(tree->left, env, iow_c);
	waitpid(-1, 0, 0);
	if (tree->token->type == AND && !exit_code)
		exit_code = exec_recursive(tree->right, env, iow);
	else if (tree->token->type == OR && exit_code)
		exit_code = exec_recursive(tree->right, env, iow);
	waitpid(-1, 0, 0);
	return (exit_code);
}

int	exec_recursive(t_tree *tree, t_env *env, int iow[3])
{
	int		exit_code;

	exit_code = 0;
	if (tree->token && tree->token->type == PIPE)
		return (exec_pipe(tree, env, iow));
	if (tree->left && tree->token
		&& (tree->token->type == OR || tree->token->type == AND))
		return (exec_cond(tree, env, iow));
	if (tree->left)
		exit_code = exec_recursive(tree->left, env, iow);
	if (tree->token && tree->token->type == WORD && tree->args)
	{
		exit_code = exec_builtin(env, iow[0], iow[1], tree);
		if (exit_code == -1)
		{
			waitpid(exec_cmd(tree, iow[0], iow[1], env), &exit_code, iow[2]);
			exit_code = WEXITSTATUS(exit_code);
		}
	}
	else if (tree && tree->redirections)
	{
		waitpid(only_redirections(iow[0], iow[1], tree), &exit_code, iow[2]);
		exit_code = WEXITSTATUS(exit_code);
	}
	if (tree->right)
		return (exec_recursive(tree->right, env, iow));
	return (exit_code);
}
