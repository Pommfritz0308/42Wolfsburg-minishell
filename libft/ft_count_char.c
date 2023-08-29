/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:26:05 by fbohling          #+#    #+#             */
/*   Updated: 2023/05/23 10:28:21 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_char(char *s, char c)
{
	int				i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}
