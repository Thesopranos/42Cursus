/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:36:40 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/10 15:36:41 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../cub3d.h"
#include <math.h>

void	rotate(t_game *g, double dir, double plane)
{
	if (g->p->right)
	{
		dir = g->p->dirx;
		g->p->dirx = g->p->dirx * cos(g->p->rot_speed)
			- g->p->diry * sin(g->p->rot_speed);
		g->p->diry = dir * sin(g->p->rot_speed)
			+ g->p->diry * cos(g->p->rot_speed);
		plane = g->planex;
		g->planex = g->planex * cos(g->p->rot_speed)
			- g->planey * sin(g->p->rot_speed);
		g->planey = plane * sin(g->p->rot_speed)
			+ g->planey * cos(g->p->rot_speed);
	}
	rotate2(g, dir, plane);
}

void	movement(t_game *game)
{
	if (game->p->w)
	{
		if (game->map->map[(int)(game->p->posy)][(int)(game->p->posx
		+ game->p->dirx * game->p->player_speed)] != '1')
			game->p->posx += game->p->dirx * game->p->player_speed;
		if (game->map->map[(int)(game->p->posy + game->p->diry
				* game->p->player_speed)][(int)(game->p->posx)] != '1')
			game->p->posy += game->p->diry * game->p->player_speed;
	}
	if (game->p->s)
	{
		if (game->map->map[(int)(game->p->posy)][(int)(game->p->posx
		- game->p->dirx * game->p->player_speed)] != '1')
			game->p->posx -= game->p->dirx * game->p->player_speed;
		if (game->map->map[(int)(game->p->posy - game->p->diry
				* game->p->player_speed)][(int)(game->p->posx)] != '1')
			game->p->posy -= game->p->diry * game->p->player_speed;
	}
	movement_2(game);
}

void	movement_2(t_game *game)
{
	if (game->p->a)
	{
		if (game->map->map[(int)(game->p->posy)][(int)(game->p->posx
				- game->planex * game->p->player_speed)] != '1')
			game->p->posx -= game->planex * game->p->player_speed;
		if (game->map->map[(int)(game->p->posy - game->planey
				* game->p->player_speed)][(int)(game->p->posx)] != '1')
			game->p->posy -= game->planey * game->p->player_speed;
	}
	if (game->p->d)
	{
		if (game->map->map[(int)(game->p->posy)][(int)(game->p->posx
				+ game->planex * game->p->player_speed)] != '1')
			game->p->posx += game->planex * game->p->player_speed;
		if (game->map->map[(int)(game->p->posy + game->planey
				* game->p->player_speed)][(int)(game->p->posx)] != '1')
			game->p->posy += game->planey * game->p->player_speed;
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
