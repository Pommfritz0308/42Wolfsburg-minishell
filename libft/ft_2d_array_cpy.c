/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_array_cpy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:34:57 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/11 18:08:51 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_2d_array_cpy(char	**src)
{
	int		i;
	char	**cpy;

	i = 0;
	while (src[i])
		i++;
	cpy = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (src[i])
	{
		cpy[i] = ft_strdup(src[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
