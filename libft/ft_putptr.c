/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:43:03 by fbohling          #+#    #+#             */
/*   Updated: 2023/03/31 11:13:49 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ptr_to_hex(unsigned long long n, int *count)
{
	if (n >= 16)
	{
		ft_ptr_to_hex(n / 16, count);
		ft_ptr_to_hex(n % 16, count);
	}
	else if (n < 16)
	{
		if (n <= 9)
			ft_putchar(n + '0', count);
		else if (n > 9)
			ft_putchar(n + 'a' - 10, count);
	}
}

void	ft_putptr(unsigned long long ptr, int *count)
{
	*count += write (1, "0x", 2);
	if (ptr == 0)
	{
		*count += write (1, "0", 1);
		return ;
	}
	ft_ptr_to_hex(ptr, count);
}
