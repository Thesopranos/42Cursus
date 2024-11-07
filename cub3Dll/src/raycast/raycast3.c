/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:56:34 by icelebi           #+#    #+#             */
/*   Updated: 2024/11/06 14:41:37 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

void	calculate_ray(t_game *game, int x)
{
	game->camerax = 2 * x / (double)WIDTH - 1;
	game->raydirx = game->dirx + game->planex * game->camerax;
	game->raydiry = game->diry + game->planey * game->camerax;
	game->mapx = (int)game->posx;
	game->mapy = (int)game->posy;
	if (game->raydirx == 0)
		game->deltadistx = 1e30;
	else
		game->deltadistx = fabs(1 / game->raydirx);
	if (game->raydiry == 0)
	{
		game->deltadisty = 1e30;
	}
	else
		game->deltadisty = fabs(1 / game->raydiry);
}

void	calculate_step(t_game *g)
{
	if (g->raydirx < 0)
	{
		g->stepx = -1;
		g->sidedistx = (g->posx - g->mapx) * g->deltadistx;
	}
	else
	{
		g->stepx = 1;
		g->sidedistx = (g->mapx + 1.0 - g->posx) * g->deltadistx;
	}
	if (g->raydiry < 0)
	{
		g->stepy = -1;
		g->sidedisty = (g->posy - g->mapy) * g->deltadisty;
	}
	else
	{
		g->stepy = 1;
		g->sidedisty = (g->mapy + 1.0 - g->posy) * g->deltadisty;
	}
}

void	calculate_hit_distance(t_game *game)
{
	int	a;

	while (1)
	{
		a = !(game->sidedistx < game->sidedisty);
		if (a == 0)
		{
			game->sidedistx += game->deltadistx;
			game->mapx += game->stepx;
			game->side = a;
		}
		else if (a == 1)
		{
			game->sidedisty += game->deltadisty;
			game->mapy += game->stepy;
			game->side = a;
		}
		if (game->map->realmap[(int)game->mapy][(int)game->mapx] == '1')
		{
			break ;
		}
	}
}

void	calculate_wall_height_x(t_game *game)
{
	game->perpwalldist = game->sidedistx - game->deltadistx;
	game->lineh = (int)(HEIGHT / game->perpwalldist);
	game->drawstart = -game->lineh / 2 + HEIGHT / 2;
	game->drawstart = (game->drawstart >= 0) * game->drawstart;
	game->drawend = game->lineh / 2 + HEIGHT / 2;
	if (game->drawend >= HEIGHT)
		game->drawend = HEIGHT - 1;
	game->wallx = game->posy + game->perpwalldist * game->raydiry;
	game->wallx = game->wallx - (int)game->wallx;
	game->texx = (int)(game->wallx * (double)TEXWIDTH);
	if (game->side == 0 && game->raydirx < 0)
		game->texx = TEXWIDTH - game->texx - 1;
	if (game->side == 1 && game->raydiry > 0)
		game->texx = TEXWIDTH - game->texx - 1;
	game->step = 1.0 * TEXHEIGHT / game->lineh;
	game->texpos = (game->drawstart - HEIGHT / 2 + game->lineh / 2)
		* game->step;
}

void	calculate_wall_height_y(t_game *game)
{
	game->perpwalldist = game->sidedisty - game->deltadisty;
	game->lineh = (int)(HEIGHT / game->perpwalldist);
	game->drawstart = -game->lineh / 2 + HEIGHT / 2;
	game->drawstart = (game->drawstart >= 0) * game->drawstart;
	game->drawend = game->lineh / 2 + HEIGHT / 2;
	if (game->drawend >= HEIGHT)
		game->drawend = HEIGHT - 1;
	game->wallx = game->posx + game->perpwalldist * game->raydirx;
	game->wallx = game->wallx - (int)game->wallx;
	game->texx = (int)(game->wallx * (double)TEXWIDTH);
	if (game->side == 0 && game->raydirx < 0)
		game->texx = TEXWIDTH - game->texx - 1;
	if (game->side == 1 && game->raydiry > 0)
		game->texx = TEXWIDTH - game->texx - 1;
	game->step = 1.0 * TEXHEIGHT / game->lineh;
	game->texpos = (game->drawstart - HEIGHT / 2 + game->lineh / 2)
		* game->step;
}
