/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 23:27:14 by mertcaki          #+#    #+#             */
/*   Updated: 2024/07/04 11:40:39 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mlx_images_free(t_game *data)
{
	if (data->player_img)
		mlx_destroy_image(data->mlxpointer, data->player_img);
	if (data->collectable)
		mlx_destroy_image(data->mlxpointer, data->collectable);
	if (data->exit)
		mlx_destroy_image(data->mlxpointer, data->exit);
	if (data->wall)
		mlx_destroy_image(data->mlxpointer, data->wall);
	data->player = NULL;
}

int	exit_point(t_game *data)
{
	int line;

	line = 0;
	if (data->winpointer)
		mlx_destroy_window(data->mlxpointer, data->winpointer);
	while (line < data->map_height)
		free(data->map[line++]);
	free(data->map);
	free(data->maplocation);
	mlx_images_free(data);
	exit(0);
}
