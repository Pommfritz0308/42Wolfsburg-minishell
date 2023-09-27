/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:30:17 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/27 12:30:20 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		tputs(tgetstr("cr", NULL), 1, tputs_putchar);
		tputs(tgetstr("el", NULL), 1, tputs_putchar);
		close(0);
	}
}

void	main_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		close(0);
}

void	main_sig_mode(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, main_handler);
	signal(SIGUSR1, main_handler);
}

void	heredoc_sig_mode(void)
{
	signal(SIGINT, heredoc_handler);
}
