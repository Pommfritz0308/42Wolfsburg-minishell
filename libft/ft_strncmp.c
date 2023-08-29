/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:38:40 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/27 17:39:10 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	i = 0;
	while ((*p1 != '\0' || *p2 != '\0') && i < n)
	{
		if (*p1 != *p2)
			return ((int)(*p1 - *p2));
		p1++;
		p2++;
		i++;
	}
	return (0);
}

// int main(void)
// {
// 	char *s1 = "\200";
//         char *s2 = "\0";
//         int i1 = ((strncmp(s1, s2, 1) > 0) ? 1
// : ((strncmp(s1, s2, 1) < 0) ? -1 : 0));
//         int i2 = ((ft_strncmp(s1, s2, 1) > 0) ? 1
// : ((ft_strncmp(s1, s2, 1) < 0) ? -1 : 0));
//         if (i1 == i2)
//             printf("S");
// 		else
//         	printf("F");
// }