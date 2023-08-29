/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:32:13 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/12 10:32:23 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_counter(int n)
{
	size_t	counter;

	counter = 0;
	if (n == 0)
		counter = 1;
	while (n != 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			digits;
	unsigned long	num;

	digits = int_counter(n);
	num = n;
	if (n < 0)
	{
		num = -num;
		digits++;
	}
	str = (char *)malloc(sizeof(char) * (digits + 1));
	if (str == NULL)
		return (NULL);
	*(str + digits) = 0;
	while (digits--)
	{
		*(str + digits) = num % 10 + 48;
		num /= 10;
	}
	if (n < 0)
		*(str + 0) = '-';
	return (str);
}

// int main(void)
// {
//     printf("string: %s\n", ft_itoa(0));
// }