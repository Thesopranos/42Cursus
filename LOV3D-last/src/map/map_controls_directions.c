/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_controls_directions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:53:19 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/10 18:09:38 by mertcaki         ###   ########.fr       */
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
	int	space_counter;

	space_counter = 0;
	space_counter = ft_skip_spaces(map->map_file[i], space_counter);
	if ((ft_strncmp(&map->map_file[i][space_counter], "SO ", 3) == 0)
		&& (map->flags->so_flag != 1))
	{
		map->so_tex_path = texture_path_handler(
				&map->map_file[i][space_counter]);
		if (!map->so_tex_path)
			ft_err_mapcontrol("so_tex_path musnt be empty", map, 1);
		map->flags->so_flag = 1;
		map->flags->flag_count++;
		return (1);
	}
	else if ((ft_strncmp(&map->map_file[i][space_counter]
			, "SO", 2) == 0) && (map->flags->so_flag == 1))
		ft_err_mapcontrol("SO more than one in map", map, 1);
	return (0);
}

int	map_no_control(t_map *map, int i)
{
	int	space_counter;

	space_counter = 0;
	space_counter = ft_skip_spaces(map->map_file[i], space_counter);
	if ((ft_strncmp(&map->map_file[i][space_counter], "NO ", 3)
		== 0) && (map->flags->no_flag != 1))
	{
		map->no_tex_path = texture_path_handler(&map->map_file[i]
			[space_counter]);
		if (!map->no_tex_path)
			ft_err_mapcontrol("no_tex_path not must empty!", map, 1);
		map->flags->no_flag = 1;
		map->flags->flag_count++;
		return (1);
	}
	else if ((ft_strncmp(&map->map_file[i][space_counter]
			, "NO", 2) == 0) && (map->flags->no_flag == 1))
		ft_err_mapcontrol("NO is more than one in map", map, 1);
	return (0);
}

int	map_ea_control(t_map *map, int i)
{
	int	space_counter;

	space_counter = 0;
	space_counter = ft_skip_spaces(map->map_file[i], 0);
	if ((ft_strncmp(&map->map_file[i][space_counter]
			, "EA ", 3) == 0) && (map->flags->ea_flag != 1))
	{
		map->ea_tex_path = texture_path_handler(&map
				->map_file[i][space_counter]);
		if (!map->ea_tex_path)
			ft_err_mapcontrol("eatexturepath not should be empty", map, 1);
		map->flags->ea_flag = 1;
		map->flags->flag_count++;
		return (1);
	}
	else if ((ft_strncmp(&map->map_file[i]
				[space_counter], "EA", 2) == 0) && (map->flags->ea_flag == 1))
		ft_err_mapcontrol("EA more than one in map", map, 1);
	return (0);
}

int	map_we_control(t_map *map, int i)
{
	int	space_counter;

	space_counter = 0;
	space_counter = ft_skip_spaces(map->map_file[i], space_counter);
	if ((ft_strncmp(&map->map_file[i][space_counter]
			, "WE ", 3) == 0) && (map->flags->we_flag != 1))
	{
		map->we_tex_path = texture_path_handler(&map->map_file[i]
			[space_counter]);
		if (!map->we_tex_path)
			ft_err_mapcontrol("we_tex_path not should be empty!", map, 1);
		map->flags->we_flag = 1;
		map->flags->flag_count++;
		return (1);
	}
	else if ((ft_strncmp(&map->map_file[i]
				[space_counter], "WE", 2) == 0) && (map->flags->we_flag == 1))
		ft_err_mapcontrol("WE more than one in map", map, 1);
	return (0);
}
