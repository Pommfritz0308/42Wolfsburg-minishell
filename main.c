/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:00:32 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/13 13:34:38 by fbohling         ###   ########.fr       */
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
		}
		free(user_input);
		if (exit_code == -1)
		{
			exit_code = EXIT_SUCCESS;
			break ;
		}
	}
	return (exit_code);
}
