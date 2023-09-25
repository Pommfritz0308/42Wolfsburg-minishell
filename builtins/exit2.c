/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:45:59 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/25 14:58:36 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit_helper(char **args, int i)
{
	while (args[1][++i])
	{
		if (!ft_isdigit(args[1][++i]))
		{
			numeric_error(args[1]);
			return (kill_util(255, args));
		}
	}
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	clean_tab(args);
	return (1);
}
