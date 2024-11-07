/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_controls_directions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:58:12 by zumgenc           #+#    #+#             */
/*   Updated: 2024/11/07 12:20:28 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>
int	try_path(char *str)
{
	int	fd;

	fd = open(str, 777);
	if (fd == -1)
		return (0);
	else
	{
		close(fd);
		return (1);
	}
}

int	map_so_control(t_map *map, int i)
{
	int space_counter = 0;
	space_counter = ft_skip_spaces(map->map[i], space_counter);

	if ((ft_strncmp(&map->map[i][space_counter], "SO ", 3) == 0) && (map->soflag != 1))
	{

		map->sotexturepath = texture_path_handler(&map->map[i][space_counter]);
		if (!map->sotexturepath)
			ft_err_mapcontrol("sotexturepath musnt be empty", map, 1);
		map->soflag = 1;
		map->flagcount++;
		return (1);
	}
	else if ((ft_strncmp(&map->map[i][space_counter], "SO", 2) == 0) && (map->soflag == 1))
		ft_err_mapcontrol("SO more than one in map", map, 1);
	return (0);
}

int	map_no_control(t_map *map, int i)
{
	int space_counter = 0;
	space_counter = ft_skip_spaces(map->map[i], space_counter);

	if ((ft_strncmp(&map->map[i][space_counter], "NO ", 3) == 0) && (map->noflag != 1))
	{
		map->notexturepath = texture_path_handler(&map->map[i][space_counter]);
		if (!map->notexturepath)
			ft_err_mapcontrol("notexturepath not must empty!", map, 1);
		map->noflag = 1;
		map->flagcount++;
		return (1);
	}
	else if ((ft_strncmp(&map->map[i][space_counter], "NO", 2) == 0) && (map->noflag == 1))
		ft_err_mapcontrol("NO is more than one in map", map, 1);
	return (0);
}

int	map_ea_control(t_map *map, int i)
{
	int space_counter = 0;
	space_counter = ft_skip_spaces(map->map[i], 0);

	if ((ft_strncmp(&map->map[i][space_counter], "EA ", 3) == 0) && (map->eaflag != 1))
	{
		map->eatexturepath = texture_path_handler(&map->map[i][space_counter]);
		if (!map->eatexturepath)
			ft_err_mapcontrol("eatexturepath not should be empty", map, 1);
		map->eaflag = 1;
		map->flagcount++;
		return (1);
	}
	else if ((ft_strncmp(&map->map[i][space_counter], "EA", 2) == 0) && (map->eaflag == 1))
		ft_err_mapcontrol("EA more than one in map", map, 1);
	return (0);
}

int	map_we_control(t_map *map, int i)
{
	int space_counter = 0;
	space_counter = ft_skip_spaces(map->map[i], space_counter);

	if ((ft_strncmp(&map->map[i][space_counter], "WE ", 3) == 0) && (map->weflag != 1))
	{
		map->wetexturepath = texture_path_handler(&map->map[i][space_counter]);
		if (!map->wetexturepath)
			ft_err_mapcontrol("wetexturepath not should be empty!", map, 1);
		map->weflag = 1;
		map->flagcount++;
		return (1);
	}
	else if ((ft_strncmp(&map->map[i][space_counter], "WE", 2) == 0) && (map->weflag == 1))
		ft_err_mapcontrol("WE more than one in map", map, 1);
	return (0);
}
