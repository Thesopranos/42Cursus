/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:58:30 by zumgenc           #+#    #+#             */
/*   Updated: 2024/11/07 18:51:36 by mertcaki         ###   ########.fr       */
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
	if (!map->map_line && map->map_line != NULL)
		free(map->map_line);
	if (!map->tmp_map && map->tmp_map != NULL)
		free_array2d(map->tmp_map);
	if (!map->realmap && map->realmap != NULL)
		free_array2d(map->realmap);
	if (!map->map && map->map != NULL)
		free_array2d(map->map);
	if (!map->map_buff && map->map_buff != NULL)
		free_array2d(map->map_buff);
	if (!map->eatexturepath && map->eatexturepath != NULL)
		free(map->eatexturepath);
	if (!map->notexturepath && map->notexturepath != NULL)
		free(map->notexturepath);
	if (!map->sotexturepath && map->sotexturepath != NULL)
		free(map->sotexturepath);
	if (!map->wetexturepath && map->wetexturepath != NULL)
		free(map->wetexturepath);
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

// !! test functions !!
void	print_map_attr(t_map *map)
{
	printf("map->mapheight = %d\n", map->mapheight);
	printf("map->path = %s\n", map->path);
	printf("map->direction = %s\n", map->direction);
	printf("map->fd = %d\n", map->fd);
	printf("map->fd_buff = %d\n", map->fd_buff);
	printf("map->realmap_height = %d\n", map->realmap_height);
	printf("map->playercount = %d\n", map->playercount);
	printf("map->pov = %c\n", map->pov);
	printf("map->map_start = %d\n", map->map_start);
	printf("map->map_start_buff = %d\n", map->map_start_buff);
	printf("map->sotexturepath = %s\n", map->sotexturepath);
	printf("map->notexturepath = %s\n", map->notexturepath);
	printf("map->eatexturepath = %s\n", map->eatexturepath);
	printf("map->wetexturepath = %s\n", map->wetexturepath);
	// printf("map->realmap = %s\n", map->realmap);
	// printf("map->tmp_map = %s\n", map->tmp_map);
	// printf("map->map_buff = %s\n", map->map_buff);
	printf("map->pos_x = %d\n", map->pos_x);
	printf("map->pos_y = %d\n", map->pos_y);
	printf("map->fcolor = %d\n", map->fcolor);
	printf("map->ccolor = %d\n", map->ccolor);
	printf("map->noflag = %d\n", map->noflag);
	printf("map->noflag_buff = %d\n", map->noflag_buff);
	printf("map->weflag = %d\n", map->weflag);
	printf("map->weflag_buff = %d\n", map->weflag_buff);
	printf("map->eaflag = %d\n", map->eaflag);
	printf("map->eaflag_buff = %d\n", map->eaflag_buff);
	printf("map->soflag = %d\n", map->soflag);
	printf("map->soflag_buff = %d\n", map->soflag_buff);
	printf("map->cflag = %d\n", map->cflag);
	printf("map->cflag_buff = %d\n", map->cflag_buff);
	printf("map->fflag = %d\n", map->fflag);
	printf("map->fflag_buff = %d\n", map->fflag_buff);
	printf("map->flagcount = %d\n", map->flagcount);
	printf("map->flagcount_buff = %d\n", map->flagcount_buff);
	printf("map->if_flag_buff = %d\n", map->if_flag_buff);
	printf("map->if_flag = %d\n", map->if_flag);
	printf("map->buff_endofflag = %d\n", map->buff_endofflag);
}
// !! test functions !!
