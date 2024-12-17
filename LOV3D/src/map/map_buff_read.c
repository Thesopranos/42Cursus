/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_buff_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:45:23 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/12 04:28:13 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void	func(t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	map->map_buff = (char **)malloc(sizeof(char *)
			* (map->map_file_height + 2));
	if (!map->map_buff)
		ft_err_mapcontrol("Map buff malloc", map, 1);
	while (1)
	{
		line = get_next_line(map->map_file_fd);
		if (!line)
			break ;
		map->map_buff[i] = ft_strdup(line);
		i++;
		free(line);
	}
	map->map_buff[i] = NULL;
	close(map->map_file_fd);
}

void	func2(t_map *map)
{
	int	i;

	i = 0;
	while (map->map_buff[i])
	{
		map_so_control_buff(map, i);
		map_no_control_buff(map, i);
		map_ea_control_buff(map, i);
		map_we_control_buff(map, i);
		map_f_control_buff(map, i);
		map_c_control_buff(map, i);
		if (map->flags->flag_count == 6)
		{
			map->buff_endofflag = i;
			break ;
		}
		i++;
	}
}

void	check_last_line(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map_buff[i] && map->map_buff[i][j])
		i++;
	if (map->map_buff[i - 1])
		while (map->map_buff[i - 1][j] != '\n')
			j++;
	if (map->map_buff[i - 1][j] != '\n')
		return ;
	if (map->map_buff[i - 1][j] != '\n')
		ft_err_mapcontrol("Map wait the newline at lastline", map, 1);
}
