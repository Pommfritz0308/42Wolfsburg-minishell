/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:24:42 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/12 13:21:05 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_checkset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i++] == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = 0;
	if (!s1 || !set)
		return (NULL);
	end = (int)ft_strlen(s1);
	while (s1[start] && ft_checkset(s1[start], set))
		start++;
	while (end > start && ft_checkset(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}

// int main()
// {
// 	printf("%s\n", ft_strtrim("x42wolfsburgyz", "xyz42"));
// 	printf("%s\n", ft_strtrim("helloabcguys", "abc"));
// 	printf("%s\n", ft_strtrim("helloabcguys", ""));
// 	printf("%s\n", ft_strtrim("", "abc"));
// 	return 0;
// }