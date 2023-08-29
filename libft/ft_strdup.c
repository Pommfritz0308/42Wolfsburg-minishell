/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:32:31 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/30 16:38:49 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;

	dest = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, (char *)s1, ft_strlen(s1) + 1);
	return (dest);
}
