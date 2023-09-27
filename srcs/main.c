/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:00:32 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/25 18:50:30 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_line(char *user_input, t_env *data)
{
	t_tree	*tree;

	add_history(user_input);
	tree = 0;
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
			clean_tab(data->env);
			exit (data->curr_exit_code);
		}
		if (user_input)
			free(user_input);
	}
}

void	exec_lines(char	*input, t_env *data)
{
	char	**line_arr;
	char	**line;
	t_tree	*tree;

	line_arr = ft_split(input, '\n');
	line = line_arr;
	while (*line)
	{
		tree = ast(*line, data);
		if (tree)
		{
			data->curr_exit_code = execute(tree, data);
			clean_tree(tree);
		}
		line++;
	}
	clean_tab(line_arr);
	clean_tab(data->env);
	exit(data->curr_exit_code);
}

int	main(int ac, char **av, char **env)
{
	t_env		data;
	char		*input;

	data = init_env(ac, av, env);
	init_settings();
	main_sig_mode();
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		input = av[2];
		data.ac = 1;
		data.av[1] = 0;
		exec_lines(input, &data);
	}
	else
		data.curr_exit_code = interactive(&data);
	return (data.curr_exit_code);
}
