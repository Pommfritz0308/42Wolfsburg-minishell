#include "../includes/minishell.h"

int	check_perms(char *word, int read, int write)
{
	struct stat	fs;

	if (read && access(word, 0) != 0)
	{
		ft_perror(word, ENOENT, 0);
		return (0);
	}
	if (write && access(word, 0) != 0)
		return (1);
	stat(word, &fs);
	if ((fs.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_perror(word, EISDIR, 0);
		return (0);
	}
	if (read && !(fs.st_mode & S_IREAD))
	{
		ft_perror(word, EACCES, 0);
		return (0);
	}
	if (write && !(fs.st_mode & S_IWRITE))
	{
		ft_perror(word, EACCES, 0);
		return (0);
	}
	return (1);
}

int	handle_out(t_rdr_l *r, int fd1)
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
			if (!check_perms(r->word, 0, 1))
				return (1);
			fd2 = open(r->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (last_char(r->token->val) == '&' || r->token->val[0] == '&')
				dup2(fd2, 2);
		}
		dup2(fd2, fd1);
	}
	if (r->token->type == REDIR_APPEND)
	{
		if (!check_perms(r->word, 0, 1))
			return (1);
		fd2 = open(r->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (last_char(r->token->val) == '&' || r->token->val[0] == '&')
			dup2(fd2, 2);
		dup2(fd2, fd1);
	}
	return (0);
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
		if (!check_perms(r->word, 1, 0))
			return (1);
		fd = open(r->word, O_RDONLY);
	}
	dup2(fd, fd1);
	return (0);
}

int last_signum = 0;

void	handler(int num)
{
	last_signum = num;
	if (num == SIGINT)
	{
		tputs(tgetstr("cr", NULL), 1, tputs_putchar);
		tputs(tgetstr("el", NULL), 1, tputs_putchar);
		close(0);
	}
}

int	handle_heredoc(t_rdr_l *r, int fd1)
{
	char	*line;
	char	*full_input;
	int		fd[2];

	if (fd1 < 0)
		fd1 = 0;
	signal(SIGINT, handler);
	if (last_signum == SIGINT)
		return (1);
	line = readline("> ");
	if (last_signum == SIGINT)
	{
		free(line);
		return (1);
	}
	full_input = (char *)malloc(sizeof(char) * 1);
	*full_input = 0;
	while (line && ft_strncmp(line, r->word, ft_strlen(r->word)))
	{
		if (last_signum == SIGINT)
		{
			free(line);
			free(full_input);
			printf("ret\n");
			return (1);
		}
		add_line(&full_input, &line);
	}
	pipe(fd);
	write(fd[1], full_input, ft_strlen(full_input));
	close(fd[1]);
	dup2(fd[0], fd1);
	free(full_input);
	return (0);
}

int	handle_open(t_rdr_l *r, int fd1)
{
	int	fd;

	if (fd1 < 0)
		fd1 = 0;
	if (!check_perms(r->word, 1, 1))
		return (1);
	fd = open(r->word, O_RDWR | O_CREAT, 0644);
	if (fd != fd1)
		dup2(fd, fd1);
	return (0);
}

int	redirections(t_rdr_l *rdrs, int *stdin_redirtected)
{
	int	fd1;
	int	exit_code;

	exit_code = 0;
	if (stdin_redirtected)
		*stdin_redirtected = 0;
	while (rdrs)
	{
		fd1 = -1;
		if (ft_isdigit(rdrs->token->val[0]))
			fd1 = ft_atoi(rdrs->token->val);
		if (!rdrs->word)
			return (ft_perror(0, SYNTAX, 2));
		if (rdrs->token->type == REDIR_OUT || rdrs->token->type == REDIR_APPEND)
			exit_code = handle_out(rdrs, fd1);
		else if (rdrs->token->type == REDIR_IN)
		{
			exit_code = handle_in(rdrs, fd1);
			if (stdin_redirtected)
				*stdin_redirtected = 1;
		}
		else if (rdrs->token->type == REDIR_HEREDOC)
		{
			exit_code = handle_heredoc(rdrs, fd1);
			if (stdin_redirtected)
				*stdin_redirtected = 1;
		}
		else if (rdrs->token->type == REDIR_OPEN)
			exit_code = handle_open(rdrs, fd1);
		rdrs = rdrs->next;
		if (exit_code)
			return (exit_code);
	}
	return (exit_code);
}
