/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:41:35 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/05 11:13:37 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*a;
	char	*b;
	size_t	i;

	a = (char *)src;
	b = (char *)dst;
	i = 0;
	if (src == NULL && dst == NULL && n > 0)
		return (dst);
	while (i < n)
	{
		b[i] = a[i];
		i++;
	}
	return (dst);
}

// int main(void)
// {
// 	char src[50] = "HelloThereMyFriends";
// 	char dest[50];
// 	char *ret1;
//     char *ret2;

// 	ret1 = ft_memcpy(((void *)0), ((void *)0), 3);
//     ret2 = memcpy(dest, src, 0);
// 	printf("test ft_memcpy: %s\n", ret1);
//     printf("test memcpy: %s\n", ret2);
// 	return (0);
// }
