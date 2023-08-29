/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:38:56 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/06 12:23:39 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	char			*a;
	char			*b;

	a = (char *)dst;
	b = (char *)src;
	i = 0;
	if (src == NULL && dst == NULL && len > 0)
		return (dst);
	if (dst > src)
	{
		while (len > 0)
		{
			a[len - 1] = b[len - 1];
			len--;
		}
		return (dst);
	}
	while (i < len)
	{
		a[i] = b[i];
		i++;
	}
	return (dst);
}
