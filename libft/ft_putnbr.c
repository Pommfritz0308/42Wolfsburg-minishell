/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:58:17 by fbohling          #+#    #+#             */
/*   Updated: 2023/03/31 11:13:42 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n, int *count)
{
	if (n == -2147483648)
	{
		*count += write (1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		*count += write (1, "-", 1);
		n = n * (-1);
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, count);
		ft_putnbr(n % 10, count);
	}
	else if (n < 10)
	{
		ft_putchar (n + '0', count);
	}
}
