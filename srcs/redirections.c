/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:30:04 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/27 12:30:05 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_append(t_rdr_l *r, int fd_left)
{
	int	fd_right;

	if (r->token->type == REDIR_APPEND)
	{
		if (!check_perms(r->word, 0, 1))
			return (1);
		fd_right = open(r->word,
				O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, 0644);
		if (fd_right < 0)
			return (ft_perror(r->word, ENOTDIR, 1));
		if (last_char(r->token->val) == '&' || r->token->val[0] == '&')
			dup2(fd_right, 2);
		dup_close(fd_right, fd_left);
	}
	return (0);
}

int	handle_out(t_rdr_l *r, int fd_left, int fd_out)
{
	int	fd_right;

	if (fd_left < 0)
		fd_left = fd_out;
	if (r->token->type == REDIR_OUT)
	{
		if (last_char(r->token->val) == '&' && is_digit(r->word))
			fd_right = ft_atoi(r->word);
		else
		{
			if (!check_perms(r->word, 0, 1))
				return (1);
			fd_right = open(r->word,
					O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
			if (fd_right < 0)
				return (ft_perror(r->word, ENOTDIR, 1));
			if (last_char(r->token->val) == '&' || r->token->val[0] == '&')
				dup2(fd_right, 2);
		}
		dup_close(fd_right, fd_left);
	}
	return (handle_append(r, fd_left));
}

int	handle_in(t_rdr_l *r, int fd_left, int fd_in)
{
	int	fd_right;

	if (fd_left < 0)
		fd_left = fd_in;
	if (last_char(r->token->val) == '&' && is_digit(r->word))
		fd_right = ft_atoi(r->word);
	else
	{
		if (!check_perms(r->word, 1, 0))
			return (1);
		fd_right = open(r->word, O_RDONLY | O_NONBLOCK | O_CLOEXEC);
		if (fd_right < 0)
			return (ft_perror(r->word, ENOTDIR, 1));
	}
	dup_close(fd_right, fd_left);
	return (0);
}

int	handle_open(t_rdr_l *r, int fd_left, int fd_in)
{
	int	fd_right;

	if (fd_left < 0)
		fd_left = fd_in;
	if (!check_perms(r->word, 1, 1))
		return (1);
	fd_right = open(r->word, O_RDWR | O_CREAT | O_NONBLOCK | O_CLOEXEC, 0644);
	if (fd_right < 0)
		return (ft_perror(r->word, ENOTDIR, 1));
	dup_close(fd_right, fd_left);
	return (0);
}

int	redirections(t_rdr_l *rdrs, int fd_in, int fd_out)
{
	int	fd_left;
	int	exit_code;

	exit_code = 0;
	while (rdrs)
	{
		fd_left = -1;
		if (ft_isdigit(rdrs->token->val[0]))
			fd_left = ft_atoi(rdrs->token->val);
		if (!rdrs->word)
			return (ft_perror(0, SYNTAX, 2));
		if (rdrs->token->type == REDIR_OUT || rdrs->token->type == REDIR_APPEND)
			exit_code = handle_out(rdrs, fd_left, fd_out);
		else if (rdrs->token->type == REDIR_IN)
			exit_code = handle_in(rdrs, fd_left, fd_in);
		else if (rdrs->token->type == REDIR_HEREDOC)
			exit_code = handle_heredoc(rdrs, fd_left, fd_in);
		else if (rdrs->token->type == REDIR_OPEN)
			exit_code = handle_open(rdrs, fd_left, fd_in);
		rdrs = rdrs->next;
		if (exit_code)
			return (exit_code);
	}
	return (exit_code);
}
