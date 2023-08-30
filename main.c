/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:00:32 by psimonen          #+#    #+#             */
/*   Updated: 2023/08/30 18:36:15 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*prompt;
	char	*user_input;
	int		exit_code;
	t_cmd	*cmds;

	handle_signals();
	exit_code = EXIT_SUCCESS;
	cmds = 0;
	while (1)
	{
		if (exit_code)
			prompt = "\e[0;31mminishell$\e[0m ";
		else
			prompt = "\e[0;32mminishell$\e[0m ";
		user_input = readline(prompt);
		add_history(user_input);
		//parse(user_input, &cmds);
		exit_code = exec_cmds(cmds);
		if (exit_code == -1)
		{
			exit_code = EXIT_SUCCESS;
			break ;
		}

	}
	return (exit_code);
}
