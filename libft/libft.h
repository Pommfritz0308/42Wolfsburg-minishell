/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:05:54 by fbohling          #+#    #+#             */
/*   Updated: 2023/09/11 18:09:21 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <ctype.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_split
{
	char		quote_flag;
	size_t		i;
	size_t		count;
	size_t		y;
}	t_split;

size_t	ft_strlen(const char *str);
void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
int		ft_strupper(char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_check_format(char c, va_list argp, int *count);
int		ft_printf(const char *str, ...);
void	ft_putchar(int c, int *count);
void	ft_putstr(char *s, int *count);
void	ft_putnbr(int n, int *count);
void	ft_dec_to_hexdec(unsigned int n, int *count, char c);
void	ft_putnbr_unsigned(unsigned int n, int *count);
void	ft_putptr(unsigned long long ptr, int *count);
char	*ft_strtolower(char *s);
double	ft_atof(char *str);
void	ft_free_array(char **arr);
char	**ft_split_with_quotations(char const *s, char c);
int		ft_count_char(char *s, char c);
void	check_for_quotes(t_split *split, char *temp);
int		ft_find_pos(char *str, char c);
int		ft_isupper(char c);
char	**ft_2d_array_cpy(char	**src);

#endif
