/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:17:04 by psimonen          #+#    #+#             */
/*   Updated: 2023/08/30 19:59:11 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("\rHi", 0);
		rl_redisplay();
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	//printf("Catched signal %d\n", signum);
}

void	handle_signals()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
}