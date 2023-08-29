/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:29:06 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/04 15:11:48 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

// int	main(void)
// {
// 	int decision = ft_isprint('z');
// 	if (decision == 0)
// 		printf("Non-printable\n");
// 	if (decision == 1)
// 		printf("Printable\n");
// 	printf("test isprint: %d\n", isprint('z'));
// }
