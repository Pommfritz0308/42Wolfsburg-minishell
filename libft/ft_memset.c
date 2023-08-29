/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:43:25 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/04 15:10:40 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len > 0)
	{
		*ptr = c;
		ptr++;
		len--;
	}
	return (b);
}

// int	main(void)
// {
// 	char str[5] = "Hello";
// 	printf("String before: %s\n", str);
// 	printf("String after ft_memset: %s\n", ft_memset(str, 'a', 3));
// 	printf("String after memset: %s\n", memset(str, 'a', 3));
// }
