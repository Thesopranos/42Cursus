/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deryacar <deryacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:04:33 by zumgenc           #+#    #+#             */
/*   Updated: 2024/11/07 01:25:30 by deryacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static bool	south_north(t_game *game)
{
	if (game->map->pov == 'S')
	{
		game->dirx = 0;
		game->diry = 1;
		game->planex = -0.66;
		game->planey = 0;
		return (true);
	}
	else if (game->map->pov == 'N')
	{
		game->dirx = 0;
		game->diry = -1.00;
		game->planex = 0.66;
		game->planey = 0;
		return (true);
	}
	return (false);
}

static bool	east_west(t_game *game)
{
	if (game->map->pov == 'W')
	{
		game->dirx = -1.0;
		game->diry = 0.0;
		game->planex = 0.0;
		game->planey = -0.66;
		return (true);
	}
	else if (game->map->pov == 'E')
	{
		game->dirx = 1.0;
		game->diry = 0.0;
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
	game->posx = game->map->pos_x + 0.5;
	game->posy = game->map->pos_y + 0.5;
	game->speed = 0.08;
	game->rspeed = 0.04;
	game->w = false;
	game->a = false;
	game->s = false;
	game->d = false;
	game->left = false;
	game->right = false;
}

int move_press(int keyCode, t_game *game)
{
    if (keyCode == KEY_EXIT)
		ft_err("exit successful", game, 0);
    if (keyCode == KEY_W)
        game->w = true;
    if (keyCode == KEY_S)
        game->s = true;
    if (keyCode == KEY_A)
        game->a = true;
    if (keyCode == KEY_D)
        game->d = true;
    if (keyCode == KEY_RIGHT)
        game->right = true;
    if (keyCode == KEY_LEFT)
        game->left = true;

    return 0;
}

