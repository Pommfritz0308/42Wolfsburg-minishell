/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:58:27 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/22 17:58:28 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(char **arg)
{
	int	i;

	i = 2;
	if (!arg || !arg[1])
		printf("\n");
	else if (!check_nl_flag(arg[1]))
	{
		if (!arg[2])
			return (EXIT_SUCCESS);
		while (!check_nl_flag(arg[i]))
			i++;
		print_args(arg, i);
	}
	else
	{
		print_args(arg, 1);
		printf("\n");
	}
	return (EXIT_SUCCESS);
}

int	check_nl_flag(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (EXIT_FAILURE);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	print_args(char **arr, int i)
{
	printf("%s", arr[i]);
	while (arr[++i])
		printf(" %s", arr[i]);
}
