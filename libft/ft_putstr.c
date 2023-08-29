/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:04:01 by fbohling          #+#    #+#             */
/*   Updated: 2023/03/31 11:13:55 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char *s, int *count)
{
	size_t	i;
	int		c;

	if (s == NULL)
	{
		*count += write(1, "(null)", 6);
		return ;
	}
	i = 0;
	while (s[i])
	{
		c = (int)s[i];
		*count += write (1, &c, 1);
		i++;
	}
}
