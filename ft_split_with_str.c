#include "minishell.h"

int	*keep(char *s1, char *s2, t_split2 *data)
{
	int	i;
	int	j;
	int	match;

	i = 0;
	match = -1;
	data->matches = malloc(data->count * sizeof(int));
	data->count = 0;
	while (i < strlen(s1))
	{
		j = 0;
		while (j < strlen(s2))
		{
			if (s1[i + j] != s2[j])
				break ;
			j++;
		}
		if (j == strlen(s2))
		{
			if (match == -1 || match + 1 == i)
			{
				match = i + j;
				data->matches[data->count] = match - strlen(s2);
				data->count++;
			}
		}
		i++;
	}
	return (data->matches);
}

// void	copy(const char *s, char *arr, size_t start, size_t count)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = start;
// 	j = 0;
// 	while (i < start + count)
// 	{
// 		arr[j] = s[i];
// 		i++;
// 		j++;
// 	}
// 	arr[j] = '\0';
// }

// char	**word_len(char *temp, char *s2, t_split *data)
// {
// 	size_t	i;
// 	size_t	count;
// 	size_t	y;

// 	i = 0;
// 	count = 0;
// 	y = 0;
// 	while (i < data->s1_len)
// 	{
// 		while ()
// 		arr[y] = calloc((count + 1), sizeof(char));
// 		copy(temp, arr[y], i - count, count);
// 		y++;
// 		count = 0;
// 	}
// 	arr[y] = NULL;
// 	return (arr);
// }

// char	**ft_split_without_delimiter(char *s)
// {
// 	char	**arr;

// 	arr = malloc(sizeof(char *) * 2);
// 	arr[0] = strdup(s);
// 	arr[1] = NULL;
// 	return (arr);
// }

void	substr_numb(char *s1, char *s2, t_split2 *data)
{
	int		j;
	int		i;
	int		match;

	data->s1_len = strlen(s1);
	data->s2_len = strlen(s2);
	data->count = 0;
	match = -1;
	i = -1;

	if (!data->s2_len)
		return ;
	while (++i < data->s1_len)
	{
		j = 0;
		while (j < data->s2_len)
		{
			if (s1[i + j] != s2[j])
				break ;
			j++;
		}
		if (j == data->s2_len)
		{
			if (match == -1 || match + 1 == i)
				data->count++;
			match = i + j;
			if (s1[match] == 0)
				data->count--;
		}
	}
}

// char	**ft_split_with_str(char *s1, char *s2)
// {
// 	t_split	split;

// 	if (!s1)
// 		return (NULL);
// 	if (*s1 == '\0')
// 	{
// 		split.arr = (char **)malloc(sizeof(char *));
// 		split.arr[0] = NULL;
// 		return (split.arr);
// 	}
// 	find_str(s1, s2, &split);
// 	if (!split.count)
// 	{
// 		split.arr = ft_split_without_delimiter((char *)s1);
// 		return (split.arr);
// 	}
// 	printf("SIZE OF 2D ARRAY: %i\n", split.count);
// 	split.arr = calloc(1 + split.count, sizeof(char *));
// 	if (!split.arr)
// 		return (NULL);
// 	split.arr = word_len(s1, s2, &split);
// 	return (split.arr);
// }

int	main(int argc, char *argv[])
{
	t_split2	split;

	int	*i;
	int	j = 0;
	// arr = ft_split_with_str(argv[1], argv[2]);
	// while (arr[++i])
	// {
	// 	printf("i: %i   >%s<\n", i, arr[i]);
	// }
	// i = -1;
	// while (arr[++i])
	// 	free(arr[i]);
	// substr_numb(argv[1], argv[2], &split);
	// printf("%i\n", split.count);
	i = keep(argv[1], argv[2], &split);
	while (j < split.count)
	{
		printf("[%i]Match at: %i\n", j, i[j]);
		j++;
	}
	free(i);
	return (0);
}
