/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:04:46 by fbohling          #+#    #+#             */
/*   Updated: 2023/04/13 09:39:36 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_atof_no_sign(char *str)
{
	double	result;
	int		decimal_found;
	double	decimal_places;

	result = 0.0;
	decimal_found = 0;
	decimal_places = 0.1;
	while (*str != '\0' && ((*str >= '0' && *str <= '9') || *str == '.'))
	{
		if (*str == '.')
		{
			decimal_found = 1;
			str++;
			continue ;
		}
		if (decimal_found)
		{
			result += (*str - '0') * decimal_places;
			decimal_places *= 0.1;
		}
		else
			result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

double	ft_atof(char *str)
{
	int	sign;

	sign = 1;
	while ((*str >= '\t' && *str <= '\r') || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	return (sign * ft_atof_no_sign(str));
}
