/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 23:27:17 by mertcaki          #+#    #+#             */
/*   Updated: 2024/07/02 16:09:38 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	place_player(t_game *data, int width, int height)
{
	mlx_put_image_to_window(data->mlxpointer, data->winpointer, data->player,
		width * RES, height * RES);
	data->player_x = width;
	data->player_y = height;
}

void	image_control(t_game *data)
{
	if (!data->player_img || !data->wall || !data->exit || !data->collectable)
	{
		ft_printf("XPM file not found");
		exit_point(data);
	}
}

void	images_in_game(t_game *data)
{
	int	i;
	int	j;

	data->player_img = mlx_xpm_file_to_image(data->mlxpointer,
			"textures/player.xpm", &i, &j);
	data->exit = mlx_xpm_file_to_image(data->mlxpointer, "textures/exit.xpm",
			&i, &j);
	data->wall = mlx_xpm_file_to_image(data->mlxpointer, "textures/wall.xpm",
			&i, &j);
	data->collectable = mlx_xpm_file_to_image(data->mlxpointer,
			"textures/food.xpm", &i, &j);
	image_control(data);
}

void	adding_graphics(t_game *data)
{
	int height;
	int width;

	height = -1;
	mlx_clear_window(data->mlxpointer, data->winpointer);
	while (++height < data->map_height)
	{
		width = -1;
		while (data->map[height][++width])
		{
			if (data->map[height][width] == '1')
				mlx_put_image_to_window(data->mlxpointer, data->winpointer,
					data->wall, width * RES, height * RES);
			if (data->map[height][width] == 'C')
				mlx_put_image_to_window(data->mlxpointer, data->winpointer,
					data->collectable, width * RES, height * RES);
			if (data->map[height][width] == 'P')
				place_player(data, width, height);
			if (data->map[height][width] == 'E')
				mlx_put_image_to_window(data->mlxpointer, data->winpointer,
					data->exit, width * RES, height * RES);
		}
	}
}
