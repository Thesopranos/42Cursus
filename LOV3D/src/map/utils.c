/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:57:19 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/11 15:37:57 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../cub3d.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_err(char *str, t_game *game, int status)
{
	if (!game)
		err_print_exit(str);
	if (game->no != NULL)
	{
		mlx_destroy_image(game->mlx, game->no->image);
		free(game->no);
	}
	if (game->so != NULL)
	{
		mlx_destroy_image(game->mlx, game->so->image);
		free(game->so);
	}
	if (game->we != NULL)
	{
		mlx_destroy_image(game->mlx, game->we->image);
		free(game->we);
	}
	if (game->ea != NULL)
	{
		mlx_destroy_image(game->mlx, game->ea->image);
		free(game->ea);
	}
	if (game->image != NULL)
		free(game->image);
	return (ft_err_mapcontrol(str, game->map, status), 0);
}

int	ft_err_mapcontrol(char *str, t_map *map, int status)
{
	if (!map)
		err_print_exit(str);
	if (!map->one_line_map && map->one_line_map != NULL)
		free(map->one_line_map);
	if (!map->tmp_map && map->tmp_map != NULL)
		free_array2d(map->tmp_map);
	if (!map->map && map->map != NULL)
		free_array2d(map->map);
	if (!map->map_file && map->map_file != NULL)
		free_array2d(map->map_file);
	if (!map->map_buff && map->map_buff != NULL)
		free_array2d(map->map_buff);
	if (!map->ea_tex_path && map->ea_tex_path != NULL)
		free(map->ea_tex_path);
	if (!map->no_tex_path && map->no_tex_path != NULL)
		free(map->no_tex_path);
	if (!map->so_tex_path && map->so_tex_path != NULL)
		free(map->so_tex_path);
	if (!map->we_tex_path && map->we_tex_path != NULL)
		free(map->we_tex_path);
	printf("%s%s%s\n", YELLOW, str, RESET);
	if (status == 1)
		printf("%sError%s\n", RED, RESET);
	exit(status);
}

void	err_print_exit(char *str)
{
	printf("%s%s%s\n%sError%s\n", YELLOW, str, RESET, RED, RESET);
	exit(1);
}

int	ft_skip_spaces(char *str, int i)
{
	if (!str)
		return (0);
	while (str[i] != '\n' && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	return (i);
}

int	all_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}
