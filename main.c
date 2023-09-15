/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:00:32 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/15 12:46:18 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*prompt;
	char		*user_input;
	int			exit_code;
	t_env		data;

	init_settings();
	data = init_env(env);
	handle_signals();
	av[0][0] = ac;
	exit_code = EXIT_SUCCESS;
	while (1)
	{
		if (exit_code)
			prompt = FAILED_PROMPT;
		else
			prompt = SUCCESS_PROMPT;
		user_input = readline(prompt);
		if (user_input && *user_input)
		{
			add_history(user_input);
			//print_ast(user_input);
			exit_code = execute(ast(user_input), &data);
			data.prev_exit_code = exit_code;
		}
		else if (!user_input)
			execute(ast("exit"), &data);
		free(user_input);
	}
	return (exit_code);
}
