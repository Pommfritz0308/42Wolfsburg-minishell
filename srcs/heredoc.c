#include "minishell.h"

int	next_heredoc(t_rdr_l *r)
{
	r = r->next;
	while (r)
	{
		if (r->token->type == REDIR_HEREDOC)
			return (1);
		r = r->next;
	}
	return (0);
}

int	handle_heredoc_helper(t_rdr_l *r, int fd_left, int fd_in)
{
	char	*line;
	char	*full_input;
	int		fd[2];

	if (fd_left < 0)
		fd_left = fd_in;
	line = readline("> ");
	if (is_closed(0))
		return (1);
	full_input = (char *)malloc(sizeof(char) * 1);
	*full_input = 0;
	while (line && ft_strncmp(line, r->word, ft_strlen(r->word)))
		add_line(&full_input, &line);
	if (line)
		free(line);
	if (is_closed(0))
	{
		free(full_input);
		return (1);
	}
	if (!next_heredoc(r))
	{
		pipe(fd);
		write(fd[1], full_input, ft_strlen(full_input));
		free(full_input);
		close(fd[1]);
		dup2(fd[0], fd_left);
	}
	return (0);
}

int	handle_heredoc(t_rdr_l *r, int fd_left, int fd_in)
{
	int	exit_code;

	heredoc_sig_mode();
	exit_code = handle_heredoc_helper(r, fd_left, fd_in);
	main_sig_mode();
	return (exit_code);
}
