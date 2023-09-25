/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:38:03 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/25 18:09:00 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_substr(char *s1, char *s2)
{
	int	n;
	int	i;
	int	j;

	i = 0;
	n = 0;
	j = 0;
	if (ft_strlen(s1) < ft_strlen(s2) || !s1 || !s2)
		return (-1);
	while (s1[i] && s2[j])
	{
		if (s1[i] == s2[j])
		{
			if (j == 0)
				n = i;
			j++;
		}
		else
			j = 0;
		i++;
	}
	if (!s2[j])
		return (n);
	else
		return (-1);
}
