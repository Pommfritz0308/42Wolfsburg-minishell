#include "minishell.h"

void	handle_out(t_rdr_l *r, int fd1)
{
	int	fd2;

	if (fd1 < 0)
		fd1 = 1;
	if (r->token->type == REDIR_OUT)
	{
		if (last_char(r->token->val) == '&' && is_digit(r->word))
			fd2 = ft_atoi(r->word);
		else
		{
			fd2 = open(r->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (last_char(r->token->val) == '&' || r->token->val[0] == '&')
				dup2(fd2, 2);
		}
		dup2(fd2, fd1);
	}
	if (r->token->type == REDIR_APPEND)
	{
		fd2 = open(r->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (last_char(r->token->val) == '&' || r->token->val[0] == '&')
			dup2(fd2, 2);
		dup2(fd2, fd1);
	}
}

int	handle_in(t_rdr_l *r, int fd1)
{
	int	fd;

	if (fd1 < 0)
		fd1 = 0;
	if (last_char(r->token->val) == '&' && is_digit(r->word))
		fd = ft_atoi(r->word);
	else
	{
		if (!access(r->word, 0))
			fd = open(r->word, O_RDONLY);
		else
		{
			ft_perror(r->word, ENOENT);
			return (127);
		}
	}
	dup2(fd, fd1);
	return (0);
}

void	handle_heredoc(t_rdr_l *r, int fd1)
{
	char	*line;
	char	*full_input;
	char	*buf;
	int		fd[2];

	if (fd1 < 0)
		fd1 = 0;
	line = readline("> ");
	full_input = (char *)malloc(sizeof(char) * 1);
	*full_input = 0;
	while (ft_strncmp(line, r->word, ft_strlen(r->word)))
	{
		buf = str_join(full_input, line, "");
		free(line);
		free(full_input);
		full_input = buf;
		buf = str_join(full_input, "\n", "");
		free(full_input);
		full_input = buf;
		line = readline("> ");
	}
	pipe(fd);
	write(fd[1], full_input, ft_strlen(full_input));
	close(fd[1]);
	dup2(fd[0], fd1);
	free(full_input);
}

void	handle_open(t_rdr_l *r, int fd1)
{
	int	fd;

	if (fd1 < 0)
		fd1 = 0;
	fd = open(r->word, O_RDWR | O_CREAT, 0644);
	if (fd != fd1)
		dup2(fd, fd1);
}

int	redirections(t_rdr_l *rdrs)
{
	int	fd1;
	int	exit_code;

	exit_code = 0;
	while (rdrs)
	{
		fd1 = -1;
		if (ft_isdigit(rdrs->token->val[0]))
			fd1 = ft_atoi(rdrs->token->val);
		if (!rdrs->word)
		{
			ft_perror(0, SYNTAX);
			return (2);
		}
		if (rdrs->token->type == REDIR_OUT || rdrs->token->type == REDIR_APPEND)
			handle_out(rdrs, fd1);
		else if (rdrs->token->type == REDIR_IN)
			exit_code = handle_in(rdrs, fd1);
		else if (rdrs->token->type == REDIR_HEREDOC)
			handle_heredoc(rdrs, fd1);
		else if (rdrs->token->type == REDIR_OPEN)
			handle_open(rdrs, fd1);
		rdrs = rdrs->next;
		if (exit_code)
			return (exit_code);
	}
	return (exit_code);
}
