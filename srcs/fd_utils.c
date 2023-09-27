#include "minishell.h"

void	wrap_ioe(int (*ioe)[3])
{
	(*ioe)[0] = dup(0);
	(*ioe)[1] = dup(1);
	(*ioe)[2] = dup(2);
}

void	restore_ioe(int (*ioe)[3])
{
	dup2((*ioe)[0], 0);
	dup2((*ioe)[1], 1);
	dup2((*ioe)[2], 2);
	close((*ioe)[0]);
	close((*ioe)[1]);
	close((*ioe)[2]);
}

int	is_closed(int fd)
{
	struct stat	st;

	if (fstat(fd, &st) == -1 && errno == EBADF)
		return (1);
	return (0);
}

void	flush_fd(int fd)
{
	char	c;

	while (read(fd, &c, 1) > 0)
		;
}

void	dup_close(int to_close, int let)
{
	if (to_close != let)
	{
		dup2(to_close, let);
		close(to_close);
	}
}
