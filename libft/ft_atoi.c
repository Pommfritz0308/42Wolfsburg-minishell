/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:21:38 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/27 17:37:39 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	if (str[0] == '\0')
		return (0);
	while ((*str >= '\t' && *str <= '\r') || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return ((int)(result * sign));
}

// int	main(void)
// {
// 	char *s = "1234";
// 	printf("test ft_atoi:%d\ntest atoi:%d\n", ft_atoi(s), atoi(s));
// }