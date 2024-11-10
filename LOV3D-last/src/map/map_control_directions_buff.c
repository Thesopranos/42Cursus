/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control_directions_buff.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:45:59 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/10 17:45:59 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

int	map_so_control_buff(t_map *map, int i)
{
	if ((ft_strncmp(map->map_buff[i], "SO ", 3) == 0)
		&& (map->buff_flags->so_flag != 1))
	{
		map->buff_flags->so_flag = 1;
		map->buff_flags->flag_count++;
		return (1);
	}
	else
		return (0);
}

int	map_no_control_buff(t_map *map, int i)
{
	if ((ft_strncmp(map->map_buff[i], "NO ", 3) == 0)
		&& (map->buff_flags->no_flag != 1))
	{
		map->buff_flags->no_flag = 1;
		map->buff_flags->flag_count++;
		return (1);
	}
	else
		return (0);
}

int	map_ea_control_buff(t_map *map, int i)
{
	if ((ft_strncmp(map->map_buff[i], "EA ", 3) == 0)
		&& (map->flags->ea_flag != 1))
	{
		map->buff_flags->ea_flag = 1;
		map->buff_flags->flag_count++;
		return (1);
	}
	else
		return (0);
}

int	map_we_control_buff(t_map *map, int i)
{
	if ((ft_strncmp(map->map_buff[i], "WE ", 3) == 0)
		&& (map->buff_flags->we_flag != 1))
	{
		map->buff_flags->we_flag = 1;
		map->buff_flags->flag_count++;
		return (1);
	}
	else
		return (0);
}

int	map_f_control_buff(t_map *map, int i)
{
	if ((ft_strncmp(map->map_buff[i], "F ", 2) == 0)
		&& (map->flags->f_flag != 1))
	{
		map->buff_flags->f_flag = 1;
		map->buff_flags->flag_count++;
		return (1);
	}
	else
		return (0);
}
