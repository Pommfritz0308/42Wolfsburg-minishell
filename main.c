/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:00:32 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/20 12:24:40 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tputs_putchar(int c)
{
	return (write(1, &c, 1));
}

int	interactive(t_env	*data)
{
	int		exit_code;
	char	*prompt;
	char	*user_input;
	t_tree	*tree;

	exit_code = EXIT_SUCCESS;
	user_input = "";
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
			tree = ast(user_input, data->prev_exit_code);
			exit_code = execute(tree, data);
			data->prev_exit_code = exit_code;
			clean_tree(tree);
		}
		else if (!user_input)
		{
			tputs(tgetstr("cr", NULL), 1, tputs_putchar);
			tputs(tgetstr("el", NULL), 1, tputs_putchar);
			exit (exit_code);
		}
		if (user_input)
			free(user_input);
	}
}

int	main(int ac, char **av, char **env)
{
	int			exit_code;
	t_env		data;
	t_tree		*tree;

	data = init_env(env);
	init_settings();
	handle_signals();
	exit_code = EXIT_SUCCESS;
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		tree = ast(av[2], data.prev_exit_code);
    	exit_code = execute(tree, &data);
		clean_tree(tree);
    	exit(exit_code);
	}
	else
		exit_code = interactive(&data);
	return (exit_code);
}
