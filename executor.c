#include "minishell.h"

char	**lst_to_tab(t_list **lst)
{
	char	**res;
	int		i;
	t_list	*buf;

	res = (char **)ft_calloc(ft_lstsize(*lst) + 1, sizeof(char *));
	if (!res)
		return (0);
	i = 0;
	while (*lst)
	{
		res[i] = ft_strdup((*lst)->content);
		free((*lst)->content);
		buf = (*lst)->next;
		free(*lst);
		*lst = buf;
		i++;
	}
	return (res);
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
		{
			full_cmd = path_to_exec(tree->args->content, env->env);
			if (!full_cmd)
				exit(127);
			if (tree->redirections)
			{
				exit_code = redirections(tree->redirections);
				if (exit_code)
					exit(exit_code);
			}
			if (execve(full_cmd, lst_to_tab(&(tree->args)), env->env) < 0)
				exit (127);
		}
	}
	return (pid);
}

void	set_iow(int fd_in, int fd_out, int wait_flag, int (*iow)[3])
{
	(*iow)[0] = fd_in;
	(*iow)[1] = fd_out;
	(*iow)[2] = wait_flag;
}

int	exec_recursive(t_tree *tree, t_env *env, int iow[3])
{
	int		fd[2];
	int		exit_code;
	int		iow_c[3];

	exit_code = 2;
	if (tree->token && tree->token->type == PIPE)
	{
		if (!tree->left || !tree->right)
		{
			ft_perror(0, SY_PIPE);
			return (2);
		}
		if (pipe(fd) < 0)
		{
			ft_perror(0, 0);
			return (EXIT_FAILURE);
		}
		set_iow(iow[0], fd[1], WNOHANG, &iow_c);
		exec_recursive(tree->left, env, iow_c);
		close(fd[1]);
		set_iow(fd[0], iow[1], iow[2], &iow_c);
		exit_code = exec_recursive(tree->right, env, iow_c);
		return (exit_code);
	}
	if (tree->left && tree->token
		&& (tree->token->type == OR || tree->token->type == AND))
	{
		if (!tree->right)
		{
			ft_perror(0, COND_ERR);
			return (2);
		}
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
	if (tree->left)
		exit_code = exec_recursive(tree->left, env, iow);
	if (tree->token && tree->token->type == WORD && tree->args)
	{
		exit_code = exec_builtin(env, iow[0], iow[1], tree);
		if (exit_code == -1)
			waitpid(exec_cmd(tree, iow[0], iow[1], env), &exit_code, iow[2]);
		exit_code = WEXITSTATUS(exit_code);
	}
	if (tree->right)
		return (exec_recursive(tree->right, env, iow));
	return (exit_code);
}

int	execute(t_tree *tree, t_env *env)
{
	int	exit_code;
	int	iow[3];

	set_iow(0, 1, 0, &iow);
	exit_code = exec_recursive(tree, env, iow);
	waitpid(-1, 0, 0);
	return (exit_code);
}
