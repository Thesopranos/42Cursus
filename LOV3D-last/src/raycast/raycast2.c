/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:39:07 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/10 15:39:07 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static bool	south_north(t_game *game)
{
	if (game->map->direction == 'S')
	{
		game->p->dirx = 0;
		game->p->diry = 1;
		game->planex = -0.66;
		game->planey = 0;
		return (true);
	}
	else if (game->map->direction == 'N')
	{
		game->p->dirx = 0;
		game->p->diry = -1.00;
		game->planex = 0.66;
		game->planey = 0;
		return (true);
	}
	return (false);
}

static bool	east_west(t_game *game)
{
	if (game->map->direction == 'W')
	{
		game->p->dirx = -1.0;
		game->p->diry = 0.0;
		game->planex = 0.0;
		game->planey = -0.66;
		return (true);
	}
	else if (game->map->direction == 'E')
	{
		game->p->dirx = 1.0;
		game->p->diry = 0.0;
		game->planex = 0.0;
		game->planey = 0.66;
		return (true);
	}
	return (false);
}

bool	check_player(t_game *game)
{
	if (east_west(game))
		return (true);
	if (south_north(game))
		return (true);
	return (false);
}

void	ray_init(t_game *game)
{
	if (!check_player(game))
		return ((void)(ft_err("Error in check player \n", game, 1)));
	game->p->posx = game->map->pos_x + 0.5;
	game->p->posy = game->map->pos_y + 0.5;
	game->p->player_speed = 0.08;
	game->p->rot_speed = 0.04;
	game->p->w = false;
	game->p->a = false;
	game->p->s = false;
	game->p->d = false;
	game->p->left = false;
	game->p->right = false;
}

int	move_press(int keyCode, t_game *game)
{
	if (keyCode == KEY_EXIT)
		ft_err("exit successful", game, 0);
	if (keyCode == KEY_W)
		game->p->w = true;
	if (keyCode == KEY_S)
		game->p->s = true;
	if (keyCode == KEY_A)
		game->p->a = true;
	if (keyCode == KEY_D)
		game->p->d = true;
	if (keyCode == KEY_RIGHT)
		game->p->right = true;
	if (keyCode == KEY_LEFT)
		game->p->left = true;
	return (0);
}
