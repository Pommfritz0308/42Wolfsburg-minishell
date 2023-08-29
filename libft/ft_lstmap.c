/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:12:16 by fbohling          #+#    #+#             */
/*   Updated: 2023/01/19 15:42:57 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_n;
	t_list	*new_l;
	t_list	*start_new_l;

	if (!lst | !f)
		return (NULL);
	new_n = ft_lstnew(f(lst->content));
	start_new_l = new_n;
	lst = lst->next;
	while (lst)
	{
		new_l = new_n;
		new_n = ft_lstnew(f(lst->content));
		if (!new_n)
		{
			ft_lstclear(&new_n, del);
			return (NULL);
		}
		ft_lstadd_back(&new_l, new_n);
		lst = lst->next;
	}
	return (start_new_l);
}
