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

int	exec_cmd(char *cmd, char **args, int fd_in, int fd_out, char **env)
{
	int		pid;
	char	*full_cmd;

	pid = fork();
	if (!pid)
	{
		if (fd_in > 0 && (dup2(fd_in, 0) < 0 || dup2(fd_out, 1) < 0))
			return (0);
		full_cmd = path_to_exec(cmd, env);
		if (execve(full_cmd, args, env) < 0)
			return (0);
	}
	return (pid);
}

int	exec_recursive(t_tree *tree, char **env, int fd_in, int fd_out)
{
	int	res;
	int	fd[2];

	if (tree->tocken && tree->tocken->type == PIPE)
	{
		pipe(fd);
		exec_recursive(tree->left, env, fd_in, fd[1]);
		close(fd[1]);
		exec_recursive(tree->right, env, fd[0], fd_out);
		return (0);
	}
	if (tree->left)
		res = exec_recursive(tree->left, env, fd_in, fd_out);
	if (tree->right && tree->tocken && tree->tocken->type == AND && !res)
		return (exec_recursive(tree->right, env, fd_in, fd_out));
	if (tree->right && tree->tocken && tree->tocken->type == OR && res)
		return (exec_recursive(tree->right, env, fd_in, fd_out));
	if (tree->args)
	{
		waitpid(exec_cmd(tree->args->content, lst_to_tab(tree->args), fd_in, fd_out, env), 0, 0);
		return (0);
	}
	else if (tree->tocken && tree->tocken->type == PIPE)
	{
		fd[0] = fd_in;
		fd[1] = fd_out;
	}
	return (0);
}

int	execute(t_tree *tree, char **env)
{
	return (exec_recursive(tree, env, 0, 1));
}