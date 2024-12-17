/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:46:37 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/12 04:29:13 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static void	all_map_control(t_map *map, int i)
{
	map_so_control(map, i);
	map_no_control(map, i);
	map_we_control(map, i);
	map_ea_control(map, i);
	map_f_control(map, i);
	map_c_control(map, i);
}

void	mapread(t_map *map)
{
	char	*line;
	char	*str;

	map->map_file_fd = open(map->map_file_path, O_RDONLY);
	if (map->map_file_fd == -1)
		err_print_exit("Failed to open map file");
	map->one_line_map = NULL;
	while (1)
	{
		line = get_next_line(map->map_file_fd);
		if (!line)
			break ;
		str = map->one_line_map;
		map->one_line_map = ft_strjoin(str, line);
		free(str);
		free(line);
	}
	if (!map->one_line_map)
		ft_err_mapcontrol("Map read error", map, 1);
	close(map->map_file_fd);
}

void	map_size(t_map *map)
{
	int	i;
	int	split_status;

	split_status = -1;
	map->map_file_height = 0;
	map->map_file = ft_adv_split(map->one_line_map, '\n', &split_status);
	if (!map->map_file)
		ft_err_mapcontrol("Map line split error", map, 1);
	i = 0;
	while (map->one_line_map[i])
	{
		if (map->one_line_map[i] == '\n')
			map->map_file_height++;
		i++;
	}
}

int	map_sixthcontrol(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map_file_height > i && map->map_file[i])
	{
		all_map_control(map, i);
		if (map->flags->flag_count == 6 && map->flags->if_flag == 0)
		{
			map->flags->if_flag = 1;
			j = i;
			break ;
		}
		i++;
	}
	if (map->flags->flag_count != 6)
		ft_err_mapcontrol("map have not 6 direction", map, 1);
	if (newline_control(map, j) == 0)
		ft_err_mapcontrol("direction partition error", map, 1);
	return (j);
}

void	skip_spaces(t_map *map, int end)
{
	int	space_counter;

	end++;
	space_counter = 0;
	if (map->map_file[end] != NULL)
	{
		while (map->map_file[end])
		{
			space_counter = ft_skip_spaces(map->map_file[end], space_counter);
			if (map->map_file[end][space_counter] == '\0')
				end++;
			else
			{
				map->map_start = end;
				break ;
			}
		}
		if (!map->map_file[end])
			map->map_start = end;
	}
	else
		ft_err_mapcontrol("map not have anything at lastline", map, 1);
}
