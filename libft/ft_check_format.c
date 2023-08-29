/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:58:00 by fbohling          #+#    #+#             */
/*   Updated: 2023/03/31 11:14:42 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_check_format(char c, va_list argp, int *count)
{
	if (c == 'c')
		ft_putchar(va_arg(argp, int), count);
	if (c == 's')
		ft_putstr(va_arg(argp, char *), count);
	if (c == '%')
		ft_putchar(c, count);
	if (c == 'i' || c == 'd')
		ft_putnbr(va_arg(argp, int), count);
	if (c == 'x' || c == 'X')
		ft_dec_to_hexdec(va_arg(argp, int), count, c);
	if (c == 'u')
		ft_putnbr_unsigned(va_arg(argp, int), count);
	if (c == 'p')
		ft_putptr(va_arg(argp, unsigned long long), count);
}
