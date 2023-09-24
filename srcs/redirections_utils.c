#include "minishell.h"

int	check_perms(char *filename, int read, int write)
{
	struct stat	fs;

	if (read && !write && access(filename, 0) != 0)
	{
		ft_perror(filename, ENOENT, 0);
		return (0);
	}
	if (write && access(filename, 0) != 0)
		return (1);
	stat(filename, &fs);
	if ((fs.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_perror(filename, EISDIR, 0);
		return (0);
	}
	if (read && !(fs.st_mode & S_IREAD))
	{
		ft_perror(filename, EACCES, 0);
		return (0);
	}
	if (write && !(fs.st_mode & S_IWRITE))
	{
		ft_perror(filename, EACCES, 0);
		return (0);
	}
	return (1);
}
