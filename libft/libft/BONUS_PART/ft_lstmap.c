/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 03:27:07 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/10 03:45:53 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*begin;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	begin = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_lst = ft_lstnew(content);
		if (!(new_lst))
		{
			(*del)(content);
			ft_lstclear(&begin, del);
			return (NULL);
		}
		ft_lstadd_back(&begin, new_lst);
		lst = lst->next;
	}
	return (begin);
}
