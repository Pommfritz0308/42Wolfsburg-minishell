/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:22:20 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/06 09:57:47 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*temp;
	size_t	len_dst;
	size_t	len_src;
	size_t	i;
	size_t	ret;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	temp = (char *)src;
	i = 0;
	if (len_dst < dstsize)
		ret = (len_dst + len_src);
	else
		ret = (len_src + dstsize);
	while (temp[i] && (len_dst + 1) < dstsize)
	{
		dst[len_dst] = temp[i];
		len_dst++;
		i++;
	}
	dst[len_dst] = '\0';
	return (ret);
}

// int	main(void)
// {
// 	char			dest[50] = "sefsfesa";
// 	char			src[50] = "Hello";
// 	unsigned int	size;

// 	size = 5;
// 	printf("%lu\n", strlcat(dest, src, size));
// 	printf("%zu\n", ft_strlcat(dest, src, size));
// 	printf("dest: %s\nsrc: %s\n", dest, src);
// }
