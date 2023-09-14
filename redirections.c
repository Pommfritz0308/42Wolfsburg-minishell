#include "minishell.h"

void	redirections(t_rdr_l *redirections)
{
	int	fd1;
	int	fd2;

	while (redirections)
	{
		printf("redir: %s", redirections->token->val);
		if (redirections->word)
			printf(" %s", redirections->word);
		printf("\n");
		fd1 = 1;
		if (ft_isdigit(redirections->token->val[0]))
			fd1 = ft_atoi(redirections->token->val);
		if (!redirections->word)
		{
			errno = SYNTAX;
			ft_perror("minishell");
		}
		if (redirections->token->type == REDIR_OUT)
		{
			fd2 = open(redirections->word, O_WRONLY | O_CREAT | O_TRUNC, 0000644);
			dup2(fd2, fd1);
		}
		else if (redirections->token->type == REDIR_IN)
		{}
		redirections = redirections->next;
	}
}
