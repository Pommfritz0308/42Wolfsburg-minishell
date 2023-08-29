/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_quotations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 10:02:36 by fbohling          #+#    #+#             */
/*   Updated: 2023/06/09 16:09:09 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	substr_numb(char *temp, char c)
{
	size_t	numb;
	size_t	i;
	char	q_flag;

	numb = 0;
	i = 0;
	q_flag = 0;
	if (temp[0] && temp[0] != c)
		numb++;
	while (temp[i])
	{
		if (temp[i] == c && !q_flag)
			numb++;
		else if (temp[i] == '"' || temp[i] == '\'')
		{
			if (!q_flag)
				q_flag = temp[i];
			else if (q_flag == temp[i])
				q_flag = 0;
		}
		i++;
	}
	return (numb);
}

static void	copy(const char *s, char *arr, size_t start, size_t count)
{
	size_t	i;
	size_t	j;

	i = start;
	j = 0;
	while (i < start + count)
	{
		arr[j] = s[i];
		i++;
		j++;
	}
	arr[j] = '\0';
}

void	check_for_quotes(t_split *split, char *temp)
{
	if (temp[split->i] == '"' || temp[split->i] == '\'')
	{
		if (split->quote_flag == '\0')
			split->quote_flag = temp[split->i];
		else if (split->quote_flag == temp[split->i])
			split->quote_flag = '\0';
	}
}

static char	**word_len(char *temp, char c, char **arr)
{
	t_split	split;

	split.i = 0;
	split.count = 0;
	split.y = 0;
	split.quote_flag = '\0';
	while (temp[split.i] != '\0')
	{
		check_for_quotes(&split, temp);
		if (split.quote_flag != '\0' || temp[split.i] != c)
			split.count++;
		if ((split.quote_flag == '\0') && (temp[split.i + 1] == c
				|| temp[split.i + 1] == '\0') && split.count > 0)
		{
			arr[split.y] = ft_calloc(split.count + 1, sizeof(char));
			if (!arr[split.y])
				return (NULL);
			copy(temp, arr[split.y], split.i - split.count + 1, split.count);
			split.y++;
			split.count = 0;
		}
		split.i++;
	}
	arr[split.y] = NULL;
	return (arr);
}

char	**ft_split_with_quotations(char const *s, char c)
{
	char	**arr;
	size_t	numb;

	if (!s)
		return (NULL);
	if (*s == '\0')
	{
		arr = (char **)malloc(sizeof(char *));
		arr[0] = NULL;
		return (arr);
	}
	if (!ft_strchr(s, c))
	{
		arr = malloc(sizeof(char *) * 2);
		arr[0] = ft_strdup(s);
		arr[1] = NULL;
		return (arr);
	}
	numb = substr_numb((char *)s, c);
	arr = ft_calloc(1 + numb, sizeof(char *));
	if (!arr)
		return (NULL);
	arr = word_len((char *)s, c, arr);
	return (arr);
}

// int main (int argc, char *argv[])
// {
// 	char **arr;
// 	int i;

// 	i = 0;
// 	if (argc != 2)
// 		return (0);
// 	arr = ft_split_with_quotations(argv[1], ' ');
// 	while (arr[i])
// 	{
// 		printf("|%s|\n", arr[i]);
// 		i++;
// 	}
// 	return (0);
// }
