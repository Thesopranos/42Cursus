/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getdatamap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:25:03 by jcluzet           #+#    #+#             */
/*   Updated: 2024/11/05 21:25:00 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	getxymap(t_parse *parse, char *filename)
{
	int		fd;
	int		b;
	// int		len;
	char	*line;

	b = 1;
	// len = 0;
	parse->sizemap.x = 1;
	parse->sizemap.y = 0;
	fd = open(filename, O_RDONLY);
	b = get_next_line(fd, &line);
	free(line);
	b = get_next_line(fd, &line);
	while (line[numberblank(line)] != '1' && line[numberblank(line)] != '2'
	&& line[numberblank(line)] != '0')
	{
		if (b != -1)
			free(line);
		b = get_next_line(fd, &line);
	}
	getxy2(parse, b, line, fd);
	close(fd);
}

void	getxy2(t_parse *parse, int b, char *line, int fd)
{
	while (b > -1 && line[0] != '\n' && line[0] != '\t' && line[0] != '\0')
	{
		if (ft_strlenght(line) > parse->sizemap.x)
			parse->sizemap.x = ft_strlenght(line);
		free(line);
		b = get_next_line(fd, &line);
		b = (b == 0 ? -1 : b);
		parse->sizemap.y++;
	}
	free(line);
}
