/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stockmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 22:23:05 by jcluzet           #+#    #+#             */
/*   Updated: 2024/11/05 22:01:34 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			stockmap(t_parse *parse, t_display *display)
{
	int		len;
	int		fd;

	len = 0;
	display->numberofplayer = 0;
	display->mapboleen = 1;
	if (display->textnum != 8)
		showerror(display, "Elements Missing");
	getxymap(parse, display->filename);
	mallocmap(parse, display);
	fd = open(display->filename, O_RDONLY);
	gotomap(display, parse, len, fd);
	close(fd);
	checkthewall(display);
	return (-1);
}

int			gotomap(t_display *display, t_parse *parse, int len, int fd)
{
	char	*line;
	int		b;

	b = get_next_line(fd, &line);
	while (line[numberblank(line)] != '1'
	&& line[numberblank(line)] != '2' && line[numberblank(line)] != '0')
	{
		if (b != -1)
			free(line);
		b = get_next_line(fd, &line);
	}
	while (line[0])
	{
		sortmap(parse, line, len, display);
		if (b > -1)
			free(line);
		len++;
		b = get_next_line(fd, &line);
	}
	free(line);
	return (0);
}

char		initposplayer(char pos, int x, int y, t_display *display)
{
	display->player.x = (double)y + 0.5;
	display->player.y = (double)x + 0.5;
	display->dirx = pos == 'E' ? -1 : 0;
	display->dirx = pos == 'W' ? 1 : display->dirx;
	display->diry = pos == 'S' ? 1 : 0;
	display->diry = pos == 'N' ? -1 : display->diry;
	display->planex = (pos == 'S') ? 0.75 : 0;
	display->planex = (pos == 'N') ? -0.75 : display->planex;
	display->planey = (pos == 'W') ? -0.75 : 0;
	display->planey = (pos == 'E') ? 0.75 : display->planey;
	display->numberofplayer++;
	return ('P');
}

int			sortmap(t_parse *parse, char *line, int len, t_display *display)
{
	int i;
	// int v;

	// v = 0;
	i = 0;
	printf("old line: %s\n", line);

	while (line[i] != '\0')
	{
		display->map[len][i] = line[i];
		replacecharinmap(display, line, i, len);
		i++;
	}
	printf("new line: %s\n", line);

	print_map(display);
	display->map[len][i] = '\0';
	while (i < parse->sizemap.x)
	{
		display->map[len][i] = ' ';
		i++;
	}
	return (1);
}

int			mallocmap(t_parse *parse, t_display *display)
{
	int i;

	i = 0;
	display->map = malloc(sizeof(char*) * (parse->sizemap.y));
	while (i < parse->sizemap.y)
	{
		display->map[i] = malloc(sizeof(char) * parse->sizemap.x + 1);
		i++;
	}
	display->mapx = parse->sizemap.x;
	display->mapy = parse->sizemap.y;
	display->maptofree = i;
	return (1);
}
