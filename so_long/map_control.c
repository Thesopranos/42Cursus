/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 23:27:27 by mertcaki          #+#    #+#             */
/*   Updated: 2024/07/04 13:50:04 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ber_control(char *mapname)
{
	int	len;

	len = ft_strlen(mapname);
	if (mapname[len - 1] != 'r' || mapname[len - 2] != 'e' || mapname[len
			- 3] != 'b' || mapname[len - 4] != '.')
		error_message("False .ber extension");
}

void	txt_control(char *mapname)
{
	int	fd;

	fd = open(mapname, O_RDONLY);
	if (fd < 0)
		error_message("Map not found");
	close(fd);
}

void	map_control(char *mapname, t_game *data)
{
	ber_control(mapname);
	data->maplocation = ft_strjoin("map/", mapname);
	txt_control(data->maplocation);
}
