/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:17:04 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/01 12:36:11 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_new_putchar(int c)
{
	return (write(1, &c, 1));
}

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		//rl_replace_line("", 0);
		//tputs(tgetstr("ce", NULL), 1, ft_new_putchar);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

void	handle_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
}
