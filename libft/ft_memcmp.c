/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:50:02 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/04 15:11:36 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (n > 0)
	{
		if (*a != *b)
			return (*a - *b);
		a++;
		b++;
		n--;
	}
	return (0);
}

// int	main(void)
// {
// 	char	str1[10] = "HelloWorld";
// 	char	str2[3] = "Hel";

// 	printf("test ft_memcmp:%d\ntest memcmp:%d\n",
// 		ft_memcmp(str1, str2, 5), memcmp(str1, str2, 5));
// }