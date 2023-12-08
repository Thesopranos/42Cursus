/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:29:53 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/08 20:30:57 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

t_list *ft_lstnew(void *content)
{
    t_list *new;

    if (!(new = (t_list*)malloc(sizeof(t_list))))
        return (NULL);
    new->content = content;
    new->next = NULL;
    return (new);
}