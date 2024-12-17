/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:56:41 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/10 17:56:41 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

void	read_real_map(t_map *map)
{
	int	i;
	int	j;

	i = map->map_start;
	j = 0;
	map->map = malloc((map->map_file_height - i) * sizeof(char *) + 1);
	if (map->map == NULL)
		ft_err_mapcontrol("Map malloc error", map, 1);
	while (map->map_file[i])
	{
		map->map[j] = ft_strdup(map->map_file[i]);
		i++;
		j++;
	}
	map->map[j] = NULL;
}

void	check_real_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] != 'W' && map->map[i][j] != 'E'
				&& map->map[i][j] != 'N' && map->map[i][j] != 'S'
				&& map->map[i][j] != '0' && map->map[i][j] != '1'
				&& map->map[i][j] != ' ')
				ft_err_mapcontrol("there is not want things in map", map, 1);
			j++;
		}
		i++;
	}
}

void	check_real_map_counts(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				map->player_count++;
				map->pos_x = j;
				map->pos_y = i;
				map->direction = map->map[i][j];
			}
			j++;
		}
		i++;
	}
	if (map->player_count != 1)
		ft_err_mapcontrol("player count much or less", map, 1);
}

void	find_height_real_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
		i++;
	map->map_height = i;
}

void	create_tmp_map(t_map *map)
{
	int	j;

	j = 0;
	map->tmp_map = malloc((map->map_height + 1) * sizeof(char *));
	if (map->tmp_map == NULL)
		ft_err_mapcontrol("tmp map malloc error", map, 1);
	while (map->map[j])
	{
		map->tmp_map[j] = ft_strdup(map->map[j]);
		j++;
	}
	map->tmp_map[j] = NULL;
}
