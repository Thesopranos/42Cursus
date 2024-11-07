/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_controls_directions2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:58:16 by zumgenc           #+#    #+#             */
/*   Updated: 2024/11/07 15:31:41 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

int	space_control(t_map *map, int i)
{
	int	j;

	j = 0;
	while ((map->map[i][j]) != '\0')
	{
		if (!(map->map[i][j] == ' ' || map->map[i][j] == '\n'))
		{
			printf("eror message");
			return (0);
		}
		j++;
	}
	return (1);
}

int	check_line_dir(char *map)
{
	int		i;
	char	c;

	i = 0;
	int space_counter = 0;
	space_counter = ft_skip_spaces(map, space_counter);
	while (map[i + space_counter])
	{
		c = map[i + space_counter];
		if ((ft_strncmp(map+space_counter, "SO ", 3) == 0) || (ft_strncmp(map+space_counter, "NO ", 3) == 0)
			|| (ft_strncmp(map+space_counter, "EA ", 3) == 0)
			|| (ft_strncmp(map+space_counter, "WE ", 3) == 0)
			|| (ft_strncmp(map+space_counter, "F ", 2) == 0)
			|| (ft_strncmp(map+space_counter, "C ", 2) == 0)
			|| c == '\0')
			return (1);
		else if (c == '\n')
			i++;
		else
			return (0);
	}
	return (1);
}

int	newline_control(t_map *map, int i)

{
	int	j;

	j = 0;
	while (j < i)
	{
		if (check_line_dir(map->map[j]) == 0)
			return (0);
		j++;
	}
	return (1);
}

int	map_f_control(t_map *map, int i)
{
	char	*str;

	str = NULL;
	int space_counter = 0;
	space_counter = ft_skip_spaces(map->map[i], space_counter);
	if ((ft_strncmp(&map->map[i][space_counter], "F ", 2) == 0) && (map->fflag != 1))
	{
		str = color_path_handler(&map->map[i][space_counter]);
		map->fcolor = take_rgb_color(str, map);
		map->fflag = 1;
		map->flagcount++;
		free(str);
		return (1);
	}
	else if ((ft_strncmp(&map->map[i][space_counter], "F", 1) == 0) && (map->fflag == 1))
	{
		free(str);
		ft_err_mapcontrol("F is more than one in map", map, 1);
	}
	return (0);
}

int	map_c_control(t_map *map, int i)
{
	char	*str;

	str = NULL;
	int space_counter = 0;
	space_counter = ft_skip_spaces(map->map[i], space_counter);
	if ((ft_strncmp(&map->map[i][space_counter], "C ", 2) == 0) && (map->cflag != 1))
	{
		str = color_path_handler(&map->map[i][space_counter]);
		map->ccolor = take_rgb_color(str, map);
		map->cflag = 1;
		map->flagcount++;
		free(str);
		return (1);
	}
	else if ((ft_strncmp(&map->map[i][space_counter], "C", 1) == 0) && (map->cflag == 1))
	{
		free(str);
		ft_err_mapcontrol("C is more than one in map", map, 1);
	}
	return (0);
}
