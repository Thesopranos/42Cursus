/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:57:14 by zumgenc           #+#    #+#             */
/*   Updated: 2024/11/10 12:20:59 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_array2d(char **str)
{
	char	**temp;

	temp = str;
	while (temp && *temp)
	{
		free(*temp);
		temp++;
	}
	free(str);
}
