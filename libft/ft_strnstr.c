/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 10:53:43 by fbohling          #+#    #+#             */
/*   Updated: 2023/05/05 14:22:28 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	a;
	size_t	b;

	if (!*needle)
		return ((char *)haystack);
	a = 0;
	b = 0;
	while (a < len && haystack[a] != '\0')
	{
		if (needle[b] == haystack[a])
		{
			b++;
			if (needle[b] == '\0')
				return ((char *)haystack + (a - b + 1));
		}
		else
		{
			a = a - b;
			b = 0;
		}
		a++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	*needle = "aabc";
// 	char	*haystack = "aaabcabcd";

// 	printf("treffer?: |%s|\n", ft_strnstr(haystack, needle, -1));
// 	printf("test strnstr: |%s|\n", strnstr(haystack, needle, -1));
// 	return (0);
// }
