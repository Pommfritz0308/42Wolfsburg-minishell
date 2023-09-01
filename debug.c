#include "minishell.h"

void	print_t_rdrct(t_rdrct *node)
{
	printf(
		"T_rdrct %p\nHeredoc:\t%d\nin_fd:\t\t%d\nlimiter:\t%s\nnext:\t\t%p\n"\
		"open_flags:\t%d\nout_fd:\t\t%d\nstderr_to_1:\t%d\nword:\t\t%s\n\n",
		node,
		node->heredoc,
		node->in_fd,
		node->limiter,
		node->next,
		node->open_flags,
		node->out_fd,
		node->stderr_to_1,
		node->word
	);
}

void	print_t_cmd(t_cmd *cmd)
{
	printf(
		"T_cmd %p\nCmd:\t\t%s\nnext:\t\t%p\nnext_cmd_cnd:\t%d\nin_rdrcts\t:%p\nout_rdrcts:\t%p\n\n",
		cmd,
		cmd->cmd,
		cmd->next_cmd,
		cmd->next_cmd_cnd,
		cmd->in_rdrcts,
		cmd->out_rdrcts
	);
}

void	print_tree(t_tree *tree)
{
	tree = 0;
}