/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:18 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/27 12:29:20 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	exec_builtin_helper(int exit_code, char **args, t_env *env)
{
	if (!ft_strncmp(args[0], "export", 7))
		exit_code = ft_export(env, args);
	else if (!ft_strncmp(args[0], "pwd", 4))
		exit_code = ft_pwd();
	else if (!ft_strncmp(args[0], "env", 4))
		exit_code = ft_env(env->env);
	else if (!ft_strncmp(args[0], "cd", 3))
		exit_code = ft_cd(env, args[1]);
	else if (!ft_strncmp(args[0], "unset", 6))
		exit_code = ft_unset(env, args);
	else if (!ft_strncmp(args[0], "echo", 5))
		exit_code = ft_echo(args);
	return (exit_code);
}

int	exec_builtin(t_env *env, int fd_in, int fd_out, t_tree *tree)
{
	int		ioe[3];
	int		exit_code;
	char	**args;

	exit_code = -1;
	if (!is_builtin(tree->args->content))
		return (exit_code);
	args = lst_to_tab(&(tree->args));
	if (!ft_strncmp(args[0], "exit", 5))
		return (ft_exit(env, args));
	wrap_ioe(&ioe);
	if (tree && tree->redirections)
		exit_code = redirections(tree->redirections, fd_in, fd_out);
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	if (exit_code <= 0)
		exit_code = exec_builtin_helper(exit_code, args, env);
	if (fd_in != 0)
		flush_fd(fd_in);
	restore_ioe(&ioe);
	clean_tab(args);
	return (exit_code);
}
