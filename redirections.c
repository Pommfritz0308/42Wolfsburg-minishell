#include "minishell.h"

void	handle_out(t_rdr_l *r, int fd1)
{
	int	fd2;

	if (fd1 < 0)
		fd1 = 1;
	if (r->token->type == REDIR_OUT)
	{
		fd2 = open(r->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd2, fd1);
	}
	if (r->token->type == REDIR_APPEND)
	{
		fd2 = open(r->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd2, fd1);
	}
}

void	handle_in(t_rdr_l *r, int fd1)
{
	int	fd;

	if (fd1 < 0)
		fd1 = 0;
	fd = open(r->word, O_RDONLY);
	dup2(fd, fd1);
}

void	handle_heredoc(t_rdr_l *r, int fd1)
{
	int	fd;

	fd = open(r->word, O_RDONLY);
	dup2(fd, fd1);
}

void	handle_close(t_rdr_l *r, int fd1)
{
	int	fd;

	fd = open(r->word, O_RDONLY);
	dup2(fd, fd1);
}

void	redirections(t_rdr_l *rdrs)
{
	int	fd1;

	fd1 = -1;
	while (rdrs)
	{
		if (ft_isdigit(rdrs->token->val[0]))
			fd1 = ft_atoi(rdrs->token->val);
		if (!rdrs->word)
		{
			errno = SYNTAX;
			ft_perror("minishell");
		}
		if (rdrs->token->type == REDIR_OUT || rdrs->token->type == REDIR_APPEND)
			handle_out(rdrs, fd1);
		else if (rdrs->token->type == REDIR_IN)
			handle_in(rdrs, fd1);
		else if (rdrs->token->type == REDIR_HEREDOC)
			handle_heredoc(rdrs, fd1);
		else if (rdrs->token->type == REDIR_CLOSE)
			handle_close(rdrs, fd1);
		rdrs = rdrs->next;
	}
}
