#include "minishell.h"

char	**lst_to_tab(t_list *lst)
{
	char	**res;
	int		i;
	t_list	*buf;

	res = (char **)ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!res)
		return (0);
	i = 0;
	while (lst)
	{
		res[i] = lst->content;
		buf = lst->next;
		free(lst);
		lst = buf;
		i++;
	}
	return (res);
}

int	exec_cmd(t_tree *tree, char **args, int fd_in, int fd_out, t_env *env)
{
	int		pid;
	char	*full_cmd;

	pid = fork();
	if (!pid)
	{
		if (dup2(fd_in, 0) < 0 || dup2(fd_out, 1) < 0)
			return (0);
		{
			full_cmd = path_to_exec(args[0], env->env);
			if (tree->redirections)
				redirections(tree->redirections);
			if (execve(full_cmd, args, env->env) < 0)
				return (0);
		}
	}
	return (pid);
}

int	exec_recursive(t_tree *tree, t_env *env, int fd_in, int fd_out, int wait_flag)
{
	int		fd[2];
	int		exit_code;
	char	**args;

	exit_code = 0;
	if (tree->tocken && tree->tocken->type == PIPE)
	{
		pipe(fd);
		exec_recursive(tree->left, env, fd_in, fd[1], WNOHANG);
		close(fd[1]);
		exit_code = exec_recursive(tree->right, env, fd[0], fd_out, wait_flag);
		return (exit_code);
	}
	if (tree->left && tree->tocken && (tree->tocken->type == OR || tree->tocken->type == AND))
	{
		exit_code = exec_recursive(tree->left, env, fd_in, fd_out, 0);
		waitpid(-1, 0, 0);
		if (tree->right && tree->tocken->type == AND && !exit_code)
			exit_code = exec_recursive(tree->right, env, fd_in, fd_out, wait_flag);
		else if (tree->right && tree->tocken->type == OR && exit_code)
			exit_code = exec_recursive(tree->right, env, fd_in, fd_out, wait_flag);
		waitpid(-1, 0, 0);
		return (exit_code);
	}
	if (tree->left)
		exit_code = exec_recursive(tree->left, env, fd_in, fd_out, wait_flag);
	if (tree->tocken && tree->tocken->type == WORD && tree->args)
	{
		args = lst_to_tab(tree->args);
		exit_code = exec_builtin(args, env);
		if (exit_code == -1)
			waitpid(exec_cmd(tree, args, fd_in, fd_out, env), &exit_code, wait_flag);
	}
	if (tree->right)
		return (exec_recursive(tree->right, env, fd_in, fd_out, wait_flag));
	return (exit_code);
}

int	execute(t_tree *tree, t_env *env)
{
	int	exit_code;

	exit_code = exec_recursive(tree, env, 0, 1, 0);
	waitpid(-1, 0, 0);
	return (exit_code);
}
