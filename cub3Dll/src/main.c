/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:21:42 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/07 15:50:03 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "./libft/libft.h"
#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

static int	check_extension(char *name)
{
	int	i;

	i = ft_strlen(name);
	if (name[i - 1] != 'b' || name[i - 2] != 'u' || name[i - 3] != 'c' || name[i
			- 4] != '.')
		return (1);
	return (0);
}

static void	check_arg(int ac, char *av, t_game *game)
{
	if (ac != 2 || check_extension(av))
		ft_err("Invalid arguments", game, 1);
}

int	exit_mlx(t_game *game)
{
	return (ft_err("exit successful", game, 0));
}

void	render_column(t_game *game, int x, int y)
{
	while (++y < HEIGHT)
	{
		game->texy = (int)game->texpos;
		if (y < game->drawstart)
			game->image->addr[y * WIDTH + x] = game->map->ccolor;
		else if (y > game->drawend)
			game->image->addr[y * WIDTH + x] = game->map->fcolor;
		else
		{
			if (game->side == 1 && game->raydiry < 0)
				game->image->addr[y * WIDTH + x] = game->no->addr[TEXHEIGHT
					* game->texy + game->texx];
			else if (game->side == 1 && game->raydiry >= 0)
				game->image->addr[y * WIDTH + x] = game->so->addr[TEXHEIGHT
					* game->texy + game->texx];
			if (game->side == 0 && game->raydirx < 0)
				game->image->addr[y * WIDTH + x] = game->we->addr[TEXHEIGHT
					* game->texy + game->texx];
			else if (game->side == 0 && game->raydirx >= 0)
				game->image->addr[y * WIDTH + x] = game->ea->addr[TEXHEIGHT
					* game->texy + game->texx];
			game->texpos += game->step;
		}
	}
}

int	main(int ac, char **av)
{
	t_map	map;
	t_game	game;

	check_arg(ac, av[1], NULL);
	game.map = &map;
	map.path = av[1];
	map_control(&map);
	ray_init(&game);
	game.mlx = mlx_init();
	if (game.mlx == NULL)
		err_print_exit("Failed to initialize MLX");

	game.mlxwin = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3D");
	ft_mlx(&game, 0, 0);
	mlx_hook(game.mlxwin, 2, 1L << 0, move_press, &game);
	mlx_hook(game.mlxwin, 3, 1L << 1, move_release, &game);
	mlx_hook(game.mlxwin, 17, 1L << 17, exit_mlx, &game);
	mlx_loop_hook(game.mlx, &gamefunc, &game);
	mlx_loop(game.mlx);
	free_map(&map);
	return (0);
}
