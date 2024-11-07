/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:57:40 by zumgenc           #+#    #+#             */
/*   Updated: 2024/11/07 15:39:47 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdlib.h>
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

static void all_map_control(t_map *map, int i)
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
	map->fd = open(map->path, O_RDONLY);
	if (map->fd == -1)
		err_print_exit("Failed to open map file");
	map->map_line = NULL;
	while (1)
	{
		line = get_next_line(map->fd);
		if (!line)
			break ;
		str = map->map_line;
		map->map_line = ft_strjoin(str, line);
		free(str);
		free(line);
	}
	if (!map->map_line)
		ft_err_mapcontrol("Map read error", map, 1);
	close(map->fd);
}

void	map_size(t_map *map)
{
	int	i;

	map->mapheight = 0;
	map->map = ft_split(map->map_line, '\n');
	if (!map->map)
	 	ft_err_mapcontrol("Map line split error", map, 1);
	i = 0;
	while (map->map_line[i])
	{
		if (map->map_line[i] == '\n')
			map->mapheight++;
		i++;
	}
	printf("map file line count = %d\n", map->mapheight);
}

int	map_sixthcontrol(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->mapheight > i && map->map[i])
	{
		all_map_control(map, i);
		if (map->flagcount == 6 && map->if_flag == 0)
		{
			map->if_flag = 1;
			j = i;
		}
		i++;
	}
	if (map->flagcount != 6)
		ft_err_mapcontrol("map have not 6 direction", map, 1);
	if (newline_control(map, j) == 0)
		ft_err_mapcontrol("direction partition error", map, 1);
	return (j);
}

void	skip_spaces(t_map *map, int end)
{
	int space_counter;

	end++;
	space_counter = 0;
	if (map->map[end] != NULL)
	{
		while (map->map[end])
		{
			space_counter = ft_skip_spaces(map->map[end], space_counter);
			if (map->map[end][space_counter] == '\0')
				end++;
			else
			{
				map->map_start = end;
				break ;
			}
		}
		if (!map->map[end])
			map->map_start = end;
	}
	else
		ft_err_mapcontrol("map not have anything at lastline", map, 1);
}
