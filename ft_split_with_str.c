#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// size_t	substr_numb(char *temp, char c)
// {
// 	size_t	numb;
// 	size_t	i;

// 	i = 0;
// 	numb = 0;
// 	if (temp[0] != c)
// 	{
// 		i = 1;
// 		numb++;
// 	}
// 	while (temp[i])
// 	{
// 		if ((i == 0 || temp[i - 1] == c) && temp[i] != c)
// 			numb++;
// 		i++;
// 	}
// 	return (numb);
// }

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

// char	**word_len(char *temp, char c, char **arr)
// {
// 	size_t	i;
// 	size_t	count;
// 	size_t	y;

// 	i = 0;
// 	count = 0;
// 	y = 0;
// 	while (temp[i] != '\0')
// 	{
// 		if (temp[i] != c)
// 			count++;
// 		i++;
// 		if ((temp[i] == c || !temp[i]) && count > 0)
// 		{
// 			arr[y] = calloc((count + 1), sizeof(char));
// 			copy(temp, arr[y], i - count, count);
// 			y++;
// 			count = 0;
// 		}
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

// char	**ft_split_with_str(char *s1, char *s2)
// {
// 	char	**arr;
// 	size_t	numb;

// 	if (!s)
// 		return (NULL);
// 	if (*s == '\0')
// 	{
// 		arr = (char **)malloc(sizeof(char *));
// 		arr[0] = NULL;
// 		return (arr);
// 	}
// 	if (!find_str(s, c))
// 	{
// 		arr = ft_split_without_delimiter((char *)s);
// 		return (arr);
// 	}
// 	numb = substr_numb((char *)s, c);
// 	arr = calloc(1 + numb, sizeof(char *));
// 	if (!arr)
// 		return (NULL);
// 	arr = word_len((char *)s, c, arr);
// 	return (arr);
// }

int	find_str(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	j = 0;
	count = 0;
	if (!s1[0] || !s2[0])
		return (0);
	while (s1[j])
    {
        if (s2[i] == s1[j])
        {
            i++;
            if (s2[i] == '\0') // Check if we have reached the end of s2
            {
                count++;
                i = 0;  // Reset i to search for the next occurrence
            }
        }
        else
        {
            i = 0;
        }
        j++;
    }
	return (count);
}

int	main(int argc, char *argv[])
{
	// char	**arr;
	// int		i;

	// i = -1;
	// arr = ft_split(argv[1], argv[2][0]);
	// while (arr[++i])
	// {
	// 	printf("i: %i   >%s<\n", i, arr[i]);
	// }
	// i = -1;
	// while (arr[++i])
	// 	free(arr[i]);
	printf("TEST: %d\n", find_str(argv[1], argv[2]));
	return (0);
}
