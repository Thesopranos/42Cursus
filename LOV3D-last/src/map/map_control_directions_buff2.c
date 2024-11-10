/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control_directions_buff2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:46:17 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/10 17:46:18 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

int	map_c_control_buff(t_map *map, int i)
{
	if ((ft_strncmp(map->map_buff[i], "C ", 2) == 0)
		&& (map->flags->c_flag != 1))
	{
		map->buff_flags->c_flag = 1;
		map->buff_flags->flag_count++;
		return (1);
	}
	else
		return (0);
}
