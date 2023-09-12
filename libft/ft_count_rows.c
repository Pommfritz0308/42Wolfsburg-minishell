/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_rows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:16:45 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/12 13:16:46 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_rows(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !arr[i])
		return (0);
	while (arr[i])
		i++;
	return (i);
}
