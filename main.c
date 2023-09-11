/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:00:32 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/11 16:43:04 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*prompt;
	char	*user_input;
	int		exit_code;
	t_cmd	*cmds;

	init_settings();
	handle_signals();
	av[0][0] = ac;
	exit_code = EXIT_SUCCESS;
	cmds = 0;
	while (1)
	{
		if (exit_code)
			prompt = FAILED_PROMPT;
		else
			prompt = SUCCESS_PROMPT;
		user_input = readline(prompt);
		if (user_input && *user_input)
			add_history(user_input);
		//print_ast(user_input);
		execute(ast(user_input), env);
		free(user_input);
		exit_code = exec_cmds(cmds);
		if (exit_code == -1)
		{
			exit_code = EXIT_SUCCESS;
			break ;
		}
	}
	return (exit_code);
}
