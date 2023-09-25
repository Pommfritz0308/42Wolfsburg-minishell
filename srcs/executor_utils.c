#include "../includes/minishell.h"

void	set_iow(int fd_in, int fd_out, int wait_flag, int (*iow)[3])
{
	(*iow)[0] = fd_in;
	(*iow)[1] = fd_out;
	(*iow)[2] = wait_flag;
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
	close(fd[0]);
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

int	exec_paranth(t_tree *tree, int iow[3], t_env *env)
{
	int	exit_code;
	int	ioe[3];

	wrap_ioe(&ioe);
	if (tree->redirections)
	{
		exit_code = redirections(tree->redirections, iow[0], iow[1]);
		if (exit_code)
		{
			restore_ioe(&ioe);
			return (exit_code);
		}
		if (dup2(iow[0], 0) < 0 || dup2(iow[1], 1) < 0)
		{
			restore_ioe(&ioe);
			return (1);
		}
	}
	if (tree->left)
		exec_recursive(tree->left, env, iow);
	exit_code = exec_recursive(tree->right, env, iow);
	waitpid(-1, 0, 0);
	restore_ioe(&ioe);
	return (exit_code);
}

int	exec_redir(t_tree *tree, int iow[3])
{
	int	exit_code;
	int	ioe[3];

	wrap_ioe(&ioe);
	exit_code = redirections(tree->redirections, iow[0], iow[1]);
	restore_ioe(&ioe);
	return (exit_code);
}
