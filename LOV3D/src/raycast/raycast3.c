/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:41:18 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/12 04:40:47 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

void	calculate_ray(t_game *game, int x)
{
	game->ray->camerax = 2 * x / (double)WIDTH - 1;
	game->ray->raydirx = game->p->dirx
		+ game->planex * game->ray->camerax;
	game->ray->raydiry = game->p->diry
		+ game->planey * game->ray->camerax;
	game->ray->mapx = (int)game->p->posx;
	game->ray->mapy = (int)game->p->posy;
	if (game->ray->raydirx == 0)
		game->ray->deltadistx = 1e30;
	else
		game->ray->deltadistx = fabs(1 / game->ray->raydirx);
	if (game->ray->raydiry == 0)
	{
		game->ray->deltadisty = 1e30;
	}
	else
		game->ray->deltadisty = fabs(1 / game->ray->raydiry);
}

void	calculate_step(t_game *g)
{
	if (g->ray->raydirx < 0)
	{
		g->ray->stepx = -1;
		g->ray->sidedistx = (g->p->posx - g->ray->mapx)
			* g->ray->deltadistx;
	}
	else
	{
		g->ray->stepx = 1;
		g->ray->sidedistx = (g->ray->mapx + 1.0 - g->p->posx)
			* g->ray->deltadistx;
	}
	if (g->ray->raydiry < 0)
	{
		g->ray->stepy = -1;
		g->ray->sidedisty = (g->p->posy - g->ray->mapy)
			* g->ray->deltadisty;
	}
	else
	{
		g->ray->stepy = 1;
		g->ray->sidedisty = (g->ray->mapy + 1.0 - g->p->posy)
			* g->ray->deltadisty;
	}
}

void	calculate_hit_distance(t_game *game)
{
	int	a;

	while (1)
	{
		a = !(game->ray->sidedistx < game->ray->sidedisty);
		if (a == 0)
		{
			game->ray->sidedistx += game->ray->deltadistx;
			game->ray->mapx += game->ray->stepx;
			game->ray->side = a;
		}
		else if (a == 1)
		{
			game->ray->sidedisty += game->ray->deltadisty;
			game->ray->mapy += game->ray->stepy;
			game->ray->side = a;
		}
		if (game->map->map[(int)game->ray->mapy][(int)game->ray->mapx] == '1')
		{
			break ;
		}
	}
}

void	calculate_wall_height_x(t_game *game)
{
	game->ray->perpwalldist = game->ray->sidedistx - game->ray->deltadistx;
	game->ray->lineh = (int)(HEIGHT / game->ray->perpwalldist);
	game->ray->drawstart = -game->ray->lineh / 2 + HEIGHT / 2;
	game->ray->drawstart = (game->ray->drawstart >= 0) * game->ray->drawstart;
	game->ray->drawend = game->ray->lineh / 2 + HEIGHT / 2;
	if (game->ray->drawend >= HEIGHT)
		game->ray->drawend = HEIGHT - 1;
	game->ray->wallx = game->p->posy + game->ray->perpwalldist
		* game->ray->raydiry;
	game->ray->wallx = game->ray->wallx - (int)game->ray->wallx;
	game->ray->texx = (int)(game->ray->wallx * (double)TEXWIDTH);
	if (game->ray->side == 0 && game->ray->raydirx < 0)
		game->ray->texx = TEXWIDTH - game->ray->texx - 1;
	if (game->ray->side == 1 && game->ray->raydiry > 0)
		game->ray->texx = TEXWIDTH - game->ray->texx - 1;
	game->step = 1.0 * TEXHEIGHT / game->ray->lineh;
	game->ray->texpos = (game->ray->drawstart - HEIGHT / 2
			+ game->ray->lineh / 2) * game->step;
}

void	calculate_wall_height_y(t_game *game)
{
	game->ray->perpwalldist = game->ray->sidedisty - game->ray->deltadisty;
	game->ray->lineh = (int)(HEIGHT / game->ray->perpwalldist);
	game->ray->drawstart = -game->ray->lineh / 2 + HEIGHT / 2;
	game->ray->drawstart = (game->ray->drawstart >= 0) * game->ray->drawstart;
	game->ray->drawend = game->ray->lineh / 2 + HEIGHT / 2;
	if (game->ray->drawend >= HEIGHT)
		game->ray->drawend = HEIGHT - 1;
	game->ray->wallx = game->p->posx + game->ray->perpwalldist
		* game->ray->raydirx;
	game->ray->wallx = game->ray->wallx - (int)game->ray->wallx;
	game->ray->texx = (int)(game->ray->wallx * (double)TEXWIDTH);
	if (game->ray->side == 0 && game->ray->raydirx < 0)
		game->ray->texx = TEXWIDTH - game->ray->texx - 1;
	if (game->ray->side == 1 && game->ray->raydiry > 0)
		game->ray->texx = TEXWIDTH - game->ray->texx - 1;
	game->step = 1.0 * TEXHEIGHT / game->ray->lineh;
	game->ray->texpos = (game->ray->drawstart - HEIGHT / 2
			+ game->ray->lineh / 2) * game->step;
}
