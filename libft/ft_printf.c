/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:14:30 by fbohling          #+#    #+#             */
/*   Updated: 2023/03/31 11:13:20 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	size_t	i;
	int		c;
	va_list	argp;
	int		count;

	count = 0;
	i = 0;
	va_start(argp, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
			ft_check_format((int)(str[++i]), argp, &count);
		else
		{
			c = (int)str[i];
			ft_putchar(c, &count);
		}
		i++;
	}
	va_end(argp);
	return (count);
}
