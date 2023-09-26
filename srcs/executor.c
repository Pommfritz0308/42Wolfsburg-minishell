#include "../includes/minishell.h"

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

int	exec_cmd(t_tree *tree, int fd_in, int fd_out, t_env *env, int to_close)
{
	int		pid;
	int		exit_code;
	char	*full_cmd;

	pid = fork();
	if (!pid)
	{
		if(to_close)
			close(to_close);
		full_cmd = path_to_exec(tree->args->content, env);
		if (!full_cmd)
			exit(env->curr_exit_code);
		if (tree->redirections)
		{
			exit_code = redirections(tree->redirections, fd_in, fd_out);
			if (exit_code)
				exit(exit_code);
		}
		if (dup2(fd_out, 1) < 0 || dup2(fd_in, 0) < 0)
			return (0);
		if (execve(full_cmd, lst_to_tab(&(tree->args)), env->env) < 0)
			exit (127);
	}
	return (pid);
}

void	add_pid(t_env *env, int pid)
{
	t_pidlst	*node;
	t_pidlst	*buf;

	if (!env)
		return ;
	node = (t_pidlst *)malloc(sizeof(t_pidlst));
	if (!node)
		return ;
	node->next = 0;
	node->pid = pid;
	if (!(env->pids))
		env->pids = node;
	else
	{
		buf = env->pids;
		while (buf && buf->next)
			buf = buf->next;
		buf->next = node;
	}
}

int	exec_cmd_helper(t_env *env, int iow[3], t_tree *tree, int to_close)
{
	int	exit_code;
	int	pid;

	if (!tree->args->content || !*((char *)tree->args->content))
		return (ft_perror(0, N_FOUND, 127));
	exit_code = exec_builtin(env, iow[0], iow[1], tree);
	if (exit_code == -1)
	{
		pid = exec_cmd(tree, iow[0], iow[1], env, to_close);
		add_pid(env, pid);
		waitpid(pid, &exit_code, iow[2]);
		exit_code = WEXITSTATUS(exit_code);
	}
	return (exit_code);
}

void	wait_all(t_env *env, int flag)
{
	t_pidlst	*buf;

	buf = env->pids;
	while (buf)
	{
		waitpid(buf->pid, 0, flag);
		buf = buf->next;
	}
}

int	exec_recursive(t_tree *tree, t_env *env, int iow[3], int to_close)
{
	int		exit_code;

	exit_code = 0;
	if (tree->token && tree->token->type == PIPE)
		return (exec_pipe(tree, env, iow));
	if (tree->token && tree->token->type == PARANTH_OPEN)
		return (exec_paranth(tree, iow, env, to_close));
	if (tree->left && tree->token
		&& (tree->token->type == OR || tree->token->type == AND))
		return (exec_cond(tree, env, iow, to_close));
	if (tree->left)
		exit_code = exec_recursive(tree->left, env, iow, to_close);
	if (tree->token && tree->token->type == WORD && tree->args)
		exit_code = exec_cmd_helper(env, iow, tree, to_close);
	else if (tree->redirections)
		exit_code = exec_redir(tree, iow);
	if (tree->right)
		exit_code = exec_recursive(tree->right, env, iow, to_close);
	wait_all(env, iow[2]);
	return (exit_code);
}

int	execute(t_tree *tree, t_env *env)
{
	int	exit_code;
	int	iow[3];

	iow[0] = 0;
	iow[1] = 1;
	iow[2] = 0;
	env->pids = 0;
	exit_code = exec_recursive(tree, env, iow, 0);
	wait_all(env, WNOHANG);
	clean_pids(env->pids);
	return (exit_code);
}
