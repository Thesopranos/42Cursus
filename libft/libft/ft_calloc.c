/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:36:16 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/10 05:12:55 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pntr;

	pntr = malloc(size * nmemb);
	if (!(pntr))
		return (NULL);
	ft_bzero(pntr, (nmemb * size));
	return (pntr);
}
