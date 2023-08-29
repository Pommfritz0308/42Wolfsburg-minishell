/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:55:39 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/04 15:12:00 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
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
// 	int decision = ft_isalpha('z');
// 	if (decision == 0)
// 		printf("Non-alphabetic\n");
// 	if (decision == 1)
// 		printf("Alphabetic\n");
// 	printf("test isalpha: %d\n", isalpha('z'));
// }