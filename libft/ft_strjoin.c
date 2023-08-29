/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:33:27 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/06 12:17:23 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;

	dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, (char *)s1, ft_strlen(s1) + 1);
	ft_strlcat(dest, (char *)s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (dest);
}

// int main(void)
// {
// 	char *s1 = "Hello";
// 	char *s2 = ", World!";
// 	char *s3 = ft_strjoin(s1, s2);

// 	printf("%s\n", s3);
// 	free(s3);

// 	return 0;
// }