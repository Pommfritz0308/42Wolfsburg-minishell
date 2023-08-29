/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:37:44 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/30 15:24:14 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;

	if (start >= ft_strlen(s))
	{
		dest = ((char *)malloc(1));
		dest[0] = '\0';
		return (dest);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	dest = ft_calloc((len + 1), sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, (char *)s + start, len + 1);
	return (dest);
}

// int	main(void)
// {
// char *substr = ft_substr("", 0, 0);
// printf("%s\n", substr);
// free(substr);
// return 0;
// }
