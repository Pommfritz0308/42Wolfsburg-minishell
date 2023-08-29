/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:28:55 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/04 15:11:56 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
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
// 	int decision = ft_isascii('z');
// 	if (decision == 0)
// 		printf("Non-ascii\n");
// 	if (decision == 1)
// 		printf("Ascii\n");
// 	printf("test isascii: %d\n", isascii('z'));
// }