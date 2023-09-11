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

int	exec_cmd(t_tree *tree)
{
	if (!fork())
	{
		execve(tree->cmd, lst_to_tab(tree->args), 0);
	}
	return (0);
}

int	execute(t_tree *tree)
{
	int	res;

	if (tree->left)
		res = execute(tree->left);
	if (tree->right && tree->tocken && tree->tocken->type == AND && !res)
		return (execute(tree->right));
	if (tree->right && tree->tocken && tree->tocken->type == OR && res)
		return (execute(tree->right));
	if (tree->cmd)
		return (exec_cmd(tree));
	return (0);
}