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

int	execute(t_tree *tree, t_env *env)
{
	int	exit_code;
	int	iow[3];
	int	ret;
	int	status;

	iow[0] = 0;
	iow[1] = 1;
	iow[2] = 0;
	exit_code = exec_recursive(tree, env, iow, 0);
	//printf("waiting line\n");
	ret = waitpid(-1, &status, 0);
	//printf("exit line %d %d status: %d\n", ret, errno, status);
	return (exit_code);
}
