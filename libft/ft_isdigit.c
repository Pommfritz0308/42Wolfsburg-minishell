/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:38:05 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/04 15:11:53 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

// int	main(void)
// {
// 	int decision = ft_isdigit('z');
// 	if (decision == 0)
// 		printf("Non-digit\n");
// 	if (decision == 1)
// 		printf("Digit\n");
// 	printf("test isdigit: %d\n", isdigit('z'));
// }
