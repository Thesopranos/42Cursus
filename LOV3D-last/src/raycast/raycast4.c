/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:45:11 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/10 15:45:12 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../cub3d.h"
#include <stdlib.h>

static void	ft_mlx2(t_game *game, int c)
{
	if (!game->no->image || !game->so->image || !game->we->image
		|| !game->ea->image)
		return ((void)(ft_err("file not opened", game, 1)));
	game->no->addr = (int *)mlx_get_data_addr(game->no->image, &c, &c, &c);
	game->so->addr = (int *)mlx_get_data_addr(game->so->image, &c, &c, &c);
	game->we->addr = (int *)mlx_get_data_addr(game->we->image, &c, &c, &c);
	game->ea->addr = (int *)mlx_get_data_addr(game->ea->image, &c, &c, &c);
	if (!game->no->addr || !game->so->addr || !game->we->addr
		|| !game->ea->addr)
		return ((void)(ft_err("file cannot read", game, 1)));
}

void	ft_mlx(t_game *game, int a, int b)
{
	game->image = malloc(sizeof(t_image));
	game->no = malloc(sizeof(t_image));
	game->so = malloc(sizeof(t_image));
	game->we = malloc(sizeof(t_image));
	game->ea = malloc(sizeof(t_image));
	if (!game->image || !game->no || !game->so || !game->we || !game->ea)
		return ((void)(ft_err("Direction malloc error", game, 1)));
	game->image->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image->image)
		return ((void)(ft_err("image malloc error", game, 1)));
	game->image->addr = (int *)mlx_get_data_addr(game->image->image, &a, &a,
			&a);
	if (!game->image->addr)
		return ((void)(ft_err("image addr malloc error", game, 1)));
	game->no->image = mlx_xpm_file_to_image(game->mlx, game->map->no_tex_path,
			&b, &b);
	game->so->image = mlx_xpm_file_to_image(game->mlx, game->map->so_tex_path,
			&b, &b);
	game->we->image = mlx_xpm_file_to_image(game->mlx, game->map->we_tex_path,
			&b, &b);
	game->ea->image = mlx_xpm_file_to_image(game->mlx, game->map->ea_tex_path,
			&b, &b);
	ft_mlx2(game, b);
}

int	move_release(int keyCode, t_game *game)
{
	if (keyCode == KEY_W)
		game->p->w = false;
	if (keyCode == KEY_S)
		game->p->s = false;
	if (keyCode == KEY_A)
		game->p->a = false;
	if (keyCode == KEY_D)
		game->p->d = false;
	if (keyCode == KEY_RIGHT)
		game->p->right = false;
	if (keyCode == KEY_LEFT)
		game->p->left = false;
	return (0);
}

void	calculate_wall_height(t_game *game)
{
	if (game->ray->side == 0)
		calculate_wall_height_x(game);
	else if (game->ray->side == 1)
		calculate_wall_height_y(game);
}
