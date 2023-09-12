#include "minishell.h"

void	redirections(t_rdr_l *redirections)
{
	while (redirections)
	{
		printf("redir: %s", redirections->token->val);
		if (redirections->word)
			printf(" %s", redirections->word);
		printf("\n");
		redirections = redirections->next;
	}
}