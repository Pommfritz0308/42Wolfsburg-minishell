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
		exit_code = redirections(tree->redirections, 0);
		exit(exit_code);
	}
	return (pid);
}

int	exec_cmd(t_tree *tree, int fd_in, int fd_out, t_env *env)
{
	int		pid;
	int		exit_code;
	char	*full_cmd;
	int		stdin_redirected;

	pid = fork();
	if (!pid)
	{
		stdin_redirected = 0;
		full_cmd = path_to_exec(tree->args->content, env);
		if (!full_cmd)
			exit(env->curr_exit_code);
		if (tree->redirections)
		{
			exit_code = redirections(tree->redirections, &stdin_redirected);
			if (exit_code)
				exit(exit_code);
		}
		if (dup2(fd_out, 1) < 0 || (!stdin_redirected && dup2(fd_in, 0) < 0))
			return (0);
		if (execve(full_cmd, lst_to_tab(&(tree->args)), env->env) < 0)
			exit (127);
	}
	return (pid);
}

int	exec_pipe(t_tree *tree, t_env *env, int iow[3], int lvl)
{
	int		exit_code;
	int		iow_c[3];
	int		fd[2];

	exit_code = 258;
	if (!tree->left || !tree->right)
	{
		//printf("exit %p\n", tree);
		return (ft_perror(0, SY_PIPE, exit_code));
	}
	if (pipe(fd) < 0)
	{
		//printf("exit %p\n", tree);
		return (ft_perror(0, 0, EXIT_FAILURE));
	}
	set_iow(iow[0], fd[1], WNOHANG, &iow_c);
	exec_recursive(tree->left, env, iow_c, lvl + 1);
	close(fd[1]);
	set_iow(fd[0], iow[1], iow[2], &iow_c);
	exit_code = exec_recursive(tree->right, env, iow_c, lvl + 1);
	//waitpid(-1, 0, 0);
	close(fd[0]);
	//printf("exit %p\n", tree);
	return (exit_code);
}

int	exec_cond(t_tree *tree, t_env *env, int iow[3], int lvl)
{
	int	exit_code;
	int	iow_c[3];

	exit_code = 258;
	if (!tree->right || !tree->left)
	{
		//printf("exit %p\n", tree);
		return (ft_perror(0, COND_ERR, exit_code));
	}
	set_iow(iow[0], iow[1], 0, &iow_c);
	exit_code = exec_recursive(tree->left, env, iow_c, lvl + 1);
	waitpid(-1, 0, 0);
	if (tree->token->type == AND && !exit_code)
		exit_code = exec_recursive(tree->right, env, iow, lvl + 1);
	else if (tree->token->type == OR && exit_code)
		exit_code = exec_recursive(tree->right, env, iow, lvl + 1);
	waitpid(-1, 0, 0);
	//printf("exit %p\n", tree);
	return (exit_code);
}

int	exec_recursive(t_tree *tree, t_env *env, int iow[3], int lvl)
{
	int		exit_code;

	exit_code = 0;
	//printf("enter %p\n", tree);
	if (tree->token && tree->token->type == PIPE)
		return (exec_pipe(tree, env, iow, lvl));
	if (tree->left && tree->token
		&& (tree->token->type == OR || tree->token->type == AND))
		return (exec_cond(tree, env, iow, lvl));
	if (tree->left)
		exit_code = exec_recursive(tree->left, env, iow, lvl + 1);
	if (tree->token && tree->token->type == WORD && tree->args)
	{
		exit_code = exec_builtin(env, iow[0], iow[1], tree);
		if (exit_code == -1)
		{
			//printf("waiting %p with status %d\n", tree, iow[2]);
			//exec_cmd(tree, iow[0], iow[1], env);
			waitpid(exec_cmd(tree, iow[0], iow[1], env), &exit_code, iow[2]);
			waitpid(0, 0, iow[2]);
			//printf("after waiting %p\n", tree);
			exit_code = WEXITSTATUS(exit_code);
		}
	}
	else if (tree && tree->redirections)
	{
		waitpid(only_redirections(iow[0], iow[1], tree), &exit_code, iow[2]);
		exit_code = WEXITSTATUS(exit_code);
	}
	if (tree->right)
	{
		//printf("exit %p\n", tree);
		return (exec_recursive(tree->right, env, iow, lvl + 1));
	}
	//printf("exit %p\n", tree);
	return (exit_code);
}
