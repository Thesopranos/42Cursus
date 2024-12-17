/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:48:03 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/12 04:28:45 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

void	free_map(t_map *map)
{
	ft_err_mapcontrol("successfully completed", map, 0);
}

void	init_struct2(t_map *map)
{
	map->pos_x = 0;
	map->pos_y = 0;
	map->player_count = 0;
	map->c_color = 0;
	map->f_color = 0;
	map->map_height = 0;
	map->ea_tex_path = NULL;
	map->we_tex_path = NULL;
	map->no_tex_path = NULL;
	map->so_tex_path = NULL;
	map->map = NULL;
	map->tmp_map = NULL;
	map->map_buff = NULL;
}

void	init_struct(t_map *map)
{
	map->flags->c_flag = 0;
	map->buff_flags->c_flag = 0;
	map->flags->f_flag = 0;
	map->buff_flags->f_flag = 0;
	map->flags->ea_flag = 0;
	map->buff_flags->ea_flag = 0;
	map->flags->flag_count = 0;
	map->buff_flags->flag_count = 0;
	map->flags->we_flag = 0;
	map->buff_flags->we_flag = 0;
	map->flags->no_flag = 0;
	map->buff_flags->no_flag = 0;
	map->flags->so_flag = 0;
	map->buff_flags->so_flag = 0;
	map->flags->if_flag = 0;
	map->map_start = 0;
	init_struct2(map);
}

void	path_finder(t_map *map, int y, int x)
{
	if (x < 0 || y < 0 || y >= map->map_height || map->tmp_map[y][x] == ' '
		|| map->tmp_map[y][x] == '\0')
		ft_err_mapcontrol("Wrong map", map, 1);
	else if (map->tmp_map[y][x] == '1')
		return ;
	map->tmp_map[y][x] = '1';
	path_finder(map, y, x - 1);
	path_finder(map, y - 1, x);
	path_finder(map, y, x + 1);
	path_finder(map, y + 1, x);
}

void	map_control(t_map *map)
{
	int	directions_end;

	directions_end = 0;
	mapread(map);
	map_size(map);
	init_struct(map);
	directions_end = map_sixthcontrol(map);
	skip_spaces(map, directions_end);
	func(map);
	func2(map);
	read_real_map(map);
	check_real_map(map);
	check_real_map_counts(map);
	find_height_real_map(map);
	create_tmp_map(map);
	path_finder(map, map->pos_y, map->pos_x);
}
