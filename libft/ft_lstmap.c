/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleonel <pleonel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:28:33 by ksharee           #+#    #+#             */
/*   Updated: 2021/03/01 19:29:20 by pleonel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_elem;
	t_list	*begin_elem;

	if (lst == NULL)
		return (NULL);
	new_elem = ft_lstnew(f(lst->content));
	if (!(new_elem))
		return (NULL);
	begin_elem = new_elem;
	lst = lst->next;
	while (lst)
	{
		new_elem = ft_lstnew(f(lst->content));
		if (!(new_elem))
		{
			ft_lstclear(&begin_elem, del);
			break ;
		}
		lst = lst->next;
		ft_lstadd_back(&begin_elem, new_elem);
	}
	return (begin_elem);
}
