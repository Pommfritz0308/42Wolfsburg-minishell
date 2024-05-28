/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:30:01 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/27 12:30:02 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_perms(char *filename, int read, int write)
{
	struct stat	fs;

	if (read && !write && access(filename, 0) != 0)
		return (ft_perror(filename, ENOENT, 0));
	if (write && access(filename, 0) != 0)
		return (1);
	stat(filename, &fs);
	if ((fs.st_mode & S_IFMT) == S_IFDIR)
		return (ft_perror(filename, EISDIR, 0));
	if (read && !(fs.st_mode & S_IREAD))
		return (ft_perror(filename, EACCES, 0));
	if (write && !(fs.st_mode & S_IWRITE))
		return (ft_perror(filename, EACCES, 0));
	return (1);
}
