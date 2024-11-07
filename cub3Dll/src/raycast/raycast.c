/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:00:57 by zumgenc           #+#    #+#             */
/*   Updated: 2024/11/06 15:20:08 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../../minilibx/mlx.h"
#include <math.h>

void	rotate(t_game *g, double dir, double plane)
{
	if (g->right)
	{
		dir = g->dirx;
		g->dirx = g->dirx * cos(g->rspeed) - g->diry * sin(g->rspeed);
		g->diry = dir * sin(g->rspeed) + g->diry * cos(g->rspeed);
		plane = g->planex;
		g->planex = g->planex * cos(g->rspeed) - g->planey * sin(g->rspeed);
		g->planey = plane * sin(g->rspeed) + g->planey * cos(g->rspeed);
	}
	if (g->left)
	{
		dir = g->dirx;
		g->dirx = g->dirx * cos(g->rspeed) + g->diry * sin(g->rspeed);
		g->diry = -dir * sin(g->rspeed) + g->diry * cos(g->rspeed);
		plane = g->planex;
		g->planex = g->planex * cos(g->rspeed) + g->planey * sin(g->rspeed);
		g->planey = -plane * sin(g->rspeed) + g->planey * cos(g->rspeed);
	}
}

void	movement(t_game *game)
{
	if (game->w)
	{
		if (game->map->realmap[(int)(game->posy)][(int)(game->posx + game->dirx
				* game->speed)] != '1')
			game->posx += game->dirx * game->speed;
		if (game->map->realmap[(int)(game->posy + game->diry
				* game->speed)][(int)(game->posx)] != '1')
			game->posy += game->diry * game->speed;
	}
	if (game->s)
	{
		if (game->map->realmap[(int)(game->posy)][(int)(game->posx - game->dirx
				* game->speed)] != '1')
			game->posx -= game->dirx * game->speed;
		if (game->map->realmap[(int)(game->posy - game->diry
				* game->speed)][(int)(game->posx)] != '1')
			game->posy -= game->diry * game->speed;
	}
	movement_2(game);
}

void	movement_2(t_game *game)
{
	if (game->a)
	{
		if (game->map->realmap[(int)(game->posy)][(int)(game->posx
				- game->planex * game->speed)] != '1')
			game->posx -= game->planex * game->speed;
		if (game->map->realmap[(int)(game->posy - game->planey
				* game->speed)][(int)(game->posx)] != '1')
			game->posy -= game->planey * game->speed;
	}
	if (game->d)
	{
		if (game->map->realmap[(int)(game->posy)][(int)(game->posx
				+ game->planex * game->speed)] != '1')
			game->posx += game->planex * game->speed;
		if (game->map->realmap[(int)(game->posy + game->planey
				* game->speed)][(int)(game->posx)] != '1')
			game->posy += game->planey * game->speed;
	}
}

static void	raycast(t_game *g)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		calculate_ray(g, x);
		calculate_step(g);
		calculate_hit_distance(g);
		calculate_wall_height(g);
		render_column(g, x, -1);
	}
	mlx_put_image_to_window(g->mlx, g->mlxwin, g->image->image, 0, 0);
}

int	gamefunc(t_game *game)
{
	movement(game);
	rotate(game, 0, 0);
	raycast(game);
	return (0);
}
