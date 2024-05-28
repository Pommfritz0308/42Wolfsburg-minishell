/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:58 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/27 12:29:59 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	left_side(t_tree *tree, t_env *env, int iow[3], int fd[2])
{
	int	pid;
	int	exit_code;
	int	iow_c[3];

	pid = fork();
	if (!pid)
	{
		set_iow(iow[0], fd[1], 0, &iow_c);
		close(fd[0]);
		exit_code = exec_recursive(tree, env, iow_c);
		close(fd[1]);
		exit(exit_code);
	}
	return (pid);
}

int	right_side(t_tree *tree, t_env *env, int iow[3], int fd[2])
{
	int	pid;
	int	exit_code;
	int	iow_c[3];

	pid = fork();
	if (!pid)
	{
		set_iow(fd[0], iow[1], iow[2], &iow_c);
		close(fd[1]);
		exit_code = exec_recursive(tree, env, iow_c);
		close(fd[0]);
		exit(exit_code);
	}
	return (pid);
}

int	exec_pipe(t_tree *tree, t_env *env, int iow[3])
{
	int		exit_code;
	int		fd[2];
	int		pids[2];

	exit_code = 258;
	if (!tree->left || !tree->right)
		return (ft_perror(0, SY_PIPE, exit_code));
	if (pipe(fd) < 0)
		return (ft_perror(0, 0, EXIT_FAILURE));
	pids[0] = left_side(tree->left, env, iow, fd);
	pids[1] = right_side(tree->right, env, iow, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pids[0], &exit_code, 0);
	waitpid(pids[1], &exit_code, 0);
	return (WEXITSTATUS(exit_code));
}
