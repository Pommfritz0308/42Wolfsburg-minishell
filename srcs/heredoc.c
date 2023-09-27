/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:29:34 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/27 12:29:35 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	write_line(char *full_input, int fd_left)
{
	int		fd[2];

	pipe(fd);
	write(fd[1], full_input, ft_strlen(full_input));
	free(full_input);
	close(fd[1]);
	dup_close(fd[0], fd_left);
}

int	handle_heredoc_helper(t_rdr_l *r, int fd_left, int fd_in)
{
	char	*line;
	char	*full_input;

	if (fd_left < 0)
		fd_left = fd_in;
	line = readline(HEREDOC_PROMPT);
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
		write_line(full_input, fd_left);
	else
		free(full_input);
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
