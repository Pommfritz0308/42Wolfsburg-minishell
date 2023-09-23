/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:00:32 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/22 14:53:06 by psimonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_line(char *user_input, t_env *data)
{
	t_tree	*tree;

	add_history(user_input);
	tree = ast(user_input, data);
	if (tree)
		data->curr_exit_code = execute(tree, data);
	data->prev_exit_code = data->curr_exit_code;
	if (tree)
		clean_tree(tree);
}

int	interactive(t_env	*data)
{
	char	*prompt;
	char	*user_input;

	while (1)
	{
		if (data->curr_exit_code)
			prompt = FAILED_PROMPT;
		else
			prompt = SUCCESS_PROMPT;
		user_input = readline(prompt);
		if (user_input && *user_input)
			exec_line(user_input, data);
		else if (!user_input)
		{
			tputs(tgetstr("cr", NULL), 1, tputs_putchar);
			tputs(tgetstr("el", NULL), 1, tputs_putchar);
			exit (data->curr_exit_code);
		}
		if (user_input)
			free(user_input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env		data;
	t_tree		*tree;
	char		*input;
	char		**line_arr;
	char		**line;

	data = init_env(ac, av, env);
	init_settings();
	handle_signals();
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		input = av[2];
		data.ac = 1;
		data.av[1] = 0;
		line_arr = ft_split(input, '\n');
		line = line_arr;
		while (*line)
		{
			tree = ast(*line, &data);
			if (tree)
			{
				data.curr_exit_code = execute(tree, &data);
				clean_tree(tree);
			}
			line++;
		}
		clean_tab(line_arr);
		exit(data.curr_exit_code);
	}
	else
		data.curr_exit_code = interactive(&data);
	return (data.curr_exit_code);
}
