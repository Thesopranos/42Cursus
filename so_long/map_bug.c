/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bug.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 23:27:24 by mertcaki          #+#    #+#             */
/*   Updated: 2024/07/04 13:46:36 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_bug(t_game *data)
{
	int	p;
	int	e;

	p = 0;
	e = 0;
	escape_line(data);
	while (++data->index.i < data->map_height)
	{
		data->index.j = -1;
		while (data->map[data->index.i][++data->index.j])
		{
			if (data->map[data->index.i][data->index.j] == 'P')
				p++;
			else if (data->map[data->index.i][data->index.j] == 'E')
				e++;
			else if (data->map[data->index.i][data->index.j] == 'C')
				data->collectables++;
			else if (data->map[data->index.i][data->index.j] != '1'
				&& data->map[data->index.i][data->index.j] != '0'
				&& data->map[data->index.i][data->index.j] != '\n')
				error_message("Unknown value on the map");
		}
	}
	if (p != 1 || e != 1 || data->collectables == 0)
		error_message("Wrong map entry");
}

static char	**create_copy_map(t_game *data)
{
	char	**new_map;
	int		i;

	new_map = (char **)malloc(sizeof(char *) * (data->map_height));
	if (new_map == NULL)
	{
		error_message("Place could not be reserved");
		exit_point(data);
	}
	i = 0;
	while (i < data->map_height)
	{
		new_map[i] = ft_strdup(data->map[i]);
		if (new_map[i] == NULL)
			break ;
		i++;
	}
	return (new_map);
}

static void	map_find(char **copy_map, int *data, int y, int x)
{
	if (copy_map[y][x] == 'C' || copy_map[y][x] == 'E')
		(*data)++;
	if (copy_map[y][x] == 'E')
		copy_map[y][x] = '1';
	if (copy_map[y][x] == '1' || copy_map[y][x] == 'E')
		return ;
	copy_map[y][x] = '1';
	map_find(copy_map, data, y + 1, x);
	map_find(copy_map, data, y - 1, x);
	map_find(copy_map, data, y, x + 1);
	map_find(copy_map, data, y, x - 1);
}

static void	copy_map_free(char **copy_map, t_game *data)
{
	int	i;

	i = 0;
	while (i < data->map_height)
	{
		free(copy_map[i]);
		i++;
	}
	free(copy_map);
}

void	placeholder(t_game *data, int y, int x)
{
	char	**copy_map;
	int		collectibles;

	collectibles = 0;
	copy_map = create_copy_map(data);
	map_find(copy_map, &collectibles, y, x);
	if (collectibles != data->collectables + 1)
	{
		copy_map_free(copy_map, data);
		error_message("Wrong Map");
		exit_point(data);
	}
	copy_map_free(copy_map, data);
}
