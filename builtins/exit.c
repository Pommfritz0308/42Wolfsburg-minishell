/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:57:38 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/25 14:58:27 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(t_env *env, char **args)
{
	int	i;

	i = -1;
	ft_putendl_fd("exit", 2);
	if (!args || !args[1])
	{
		clean_tab(args);
		kill(0, SIGUSR1);
		return (env->curr_exit_code);
	}
	if (ft_count_rows(args) > 2)
		return (ft_exit_helper(args, i));
	else if (ft_atoi(args[1]) > 255 || ft_atoi(args[1]) < 0)
	{
		if (!calc_exit_code(env, args[1]))
			return (kill_util(255, args));
		else
			return (kill_util(env->curr_exit_code, args));
	}
	return (kill_util(ft_atoi(args[1]), args));
}

int	calc_exit_code(t_env *env, char *numb)
{
	long long int	result;
	int				sign;
	int				i;

	i = 0;
	sign = 1;
	result = 0;
	while (numb[i] == ' ' || numb[i] == '\t')
		i++;
	if (numb[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (numb[i] == '+')
		i++;
	while (numb[i] >= '0' && numb[i] <= '9')
	{
		if (!check_range(result, numb, i))
			return (false);
		result = result * 10 + (numb[i] - '0');
		i++;
	}
	env->curr_exit_code = (int)((result * sign) % 256);
	return (true);
}

void	numeric_error(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

bool	check_range(long long int result, char *numb, int i)
{
	if (result > LLONG_MAX / 10 || (result == LLONG_MAX
			/ 10 && (numb[i] - '0') > LLONG_MAX % 10))
	{
		numeric_error(numb);
		return (false);
	}
	return (true);
}

int	kill_util(int exit_code, char **args)
{
	clean_tab(args);
	kill(0, SIGUSR1);
	return (exit_code);
}
