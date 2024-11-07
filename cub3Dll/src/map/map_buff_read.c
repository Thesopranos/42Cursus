/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_buff_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:57:23 by zumgenc           #+#    #+#             */
/*   Updated: 2024/11/07 19:06:29 by mertcaki         ###   ########.fr       */
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
	int		j;
	int		is_all_space;

	j = 0;
	i = 0;
	map->fd_buff = open(map->path, O_RDONLY);
	if (map->fd_buff == -1)
		ft_err_mapcontrol("Failed to open map file", map, 1);
	map->map_buff = (char **)malloc(sizeof(char *) * (map->mapheight + 2));
	if (!map->map_buff)
		ft_err_mapcontrol("Map buff malloc", map, 1);
	while (1)
	{
		line = get_next_line(map->fd_buff);
		if (!line)
			break ;
		j = 0;
		is_all_space = 0;
		while ((line[j] == ' ' || (9 <= line[j] && line[j] <= 13))
			&& line[j] != '\n')
		{
			j++;
			if (!(line[j] <= 127 && line[j] >= 41))
				is_all_space = 0;
			else if (line[j] == '\n')
				is_all_space = 1;
		}
		if (!line[0] || is_all_space)
			continue ;
		else
		{
			map->map_buff[i] = ft_strdup(line);
			if (!map->map_buff[i])
				ft_err_mapcontrol("Map buff strdup", map, 1);
			i++;
		}
		free(line);
	}
	map->map_buff[i] = NULL;
	close(map->fd_buff);
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
		if (map->flagcount_buff == 6 && map->if_flag_buff == 0)
		{
			map->if_flag_buff = 1;
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
void	cutted_map_control(t_map *map, char *line)
{
	if ((int)ft_strlen(line) == ft_skip_spaces(line, 0))
		ft_err_mapcontrol("Map have empty line", map, 1);
}
