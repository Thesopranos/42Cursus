/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deryacar <deryacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:25:05 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/12 04:53:25 by deryacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "./libft/libft.h"
#include "cub3d.h"
#include <stdlib.h>

static void	check_arg(int ac, char *av, t_game *game)
{
	int	i;

	i = ft_strlen(av);
	if (ac != 2)
		ft_err("Invalid argument count", game, 1);
	else if (av[i - 1] != 'b' || av[i - 2] != 'u' || av[i - 3] != 'c' || av[i
			- 4] != '.')
		ft_err("Invalid file extension", game, 1);
}

int	exit_mlx(t_game *game)
{
	return (ft_err("exit successful", game, 0));
}

void	render_column(t_game *game, int x, int y)
{
	while (++y < HEIGHT)
	{
		game->ray->texy = (int)game->ray->texpos;
		if (y < game->ray->drawstart)
			game->image->addr[y * WIDTH + x] = game->map->c_color;
		else if (y > game->ray->drawend)
			game->image->addr[y * WIDTH + x] = game->map->f_color;
		else
		{
			if (game->ray->side == 1 && game->ray->raydiry < 0)
				game->image->addr[y * WIDTH + x] = game->no->addr[TEXHEIGHT
					* game->ray->texy + game->ray->texx];
			else if (game->ray->side == 1 && game->ray->raydiry >= 0)
				game->image->addr[y * WIDTH + x] = game->so->addr[TEXHEIGHT
					* game->ray->texy + game->ray->texx];
			if (game->ray->side == 0 && game->ray->raydirx < 0)
				game->image->addr[y * WIDTH + x] = game->we->addr[TEXHEIGHT
					* game->ray->texy + game->ray->texx];
			else if (game->ray->side == 0 && game->ray->raydirx >= 0)
				game->image->addr[y * WIDTH + x] = game->ea->addr[TEXHEIGHT
					* game->ray->texy + game->ray->texx];
			game->ray->texpos += game->step;
		}
	}
}

static void	initialize_flags(t_map *map)
{
	t_flags	*flags;
	t_flags	*buff_flags;

	flags = (t_flags *)malloc(sizeof(t_flags));
	if (!flags)
		ft_err_mapcontrol("Flags malloc error", map, 1);
	buff_flags = (t_flags *)malloc(sizeof(t_flags));
	if (!buff_flags)
		ft_err_mapcontrol("Flags malloc error", map, 1);
	map->flags = flags;
	map->buff_flags = buff_flags;
}

int	main(int ac, char **av)
{
	t_game		game;
	t_map		map;
	t_player	player;
	t_ray		ray;

	check_arg(ac, av[1], NULL);
	game.map = &map;
	initialize_flags(&map);
	game.p = &player;
	game.ray = &ray;
	map.map_file_path = av[1];
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
