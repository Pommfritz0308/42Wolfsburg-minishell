/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atolli.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:02:02 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/25 16:02:03 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_atolli(const char *str)
{
	long long int	result;
	int				sign;
	int				i;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = ft_atolli_helper(result, sign, str, i);
		if (result == LLONG_MAX || result == LLONG_MIN)
			return (result);
		i++;
	}
	return (result * sign);
}

long long int	ft_atolli_helper(long long int result,
	int sign, char *str, int i)
{
	if (result > LLONG_MAX / 10 || (result == LLONG_MAX
			/ 10 && (str[i] - '0') > LLONG_MAX % 10))
	{
		if (sign == 1)
			return (LLONG_MAX);
		else
			return (LLONG_MIN);
	}
	return (result * 10 + (str[i] - '0'));
}
