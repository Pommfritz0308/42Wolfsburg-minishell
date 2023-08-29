/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dec_to_hexdec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:45:30 by fbohling          #+#    #+#             */
/*   Updated: 2023/03/31 11:14:47 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dec_to_hexdec(unsigned int n, int *count, char c)
{
	if (n >= 16)
	{
		ft_dec_to_hexdec(n / 16, count, c);
		ft_dec_to_hexdec(n % 16, count, c);
	}
	else if (n < 16)
	{
		if (n <= 9)
			ft_putchar(n + '0', count);
		else if (n > 9 && c == 'X')
			ft_putchar(n + 'A' - 10, count);
		else if (n > 9 && c == 'x')
			ft_putchar(n + 'a' - 10, count);
	}
}
