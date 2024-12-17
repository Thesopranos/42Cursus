/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:44:51 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/10 17:44:52 by mertcaki         ###   ########.fr       */
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
