/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 22:23:05 by jcluzet           #+#    #+#             */
/*   Updated: 2024/11/05 20:47:49 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse(int argc, char *str, t_parse *parse, t_display *display)
{
	int		fd;

	if (argc == 3)
		display->bmp = 1;
	else
		display->bmp = 0;
	if ((display->filename = malloc(sizeof(char)
	* strlentoend(str) + 1)) == NULL)
		showerror(display, "Unable to Malloc");
	checkcubextension(str, display);
	ft_strcpy(display->filename, str);
	fd = open(str, O_RDONLY);
	display->fd = fd;
	checkparse(display, parse, fd);
	return (1);
}

int	checkparse(t_display *display, t_parse *parse, int fd)
{
	int		u;
	char	*line;

	u = 0;
	while (u > -1)
	{
		u = get_next_line(fd, &line);
		if (line[numberblank(line)] == '1' || u == 0)
			u = -1;
		if (parseline(line, parse, display) == -1)
			u = -1;
		free(line);
	}
	close(fd);
	if (display->textnum < 8)
		showerror(display, "Elements Missing");
	if (display->textnum > 8)
		showerror(display, "Duplicate Element");
	if (display->mapboleen == 0)
		showerror(display, "Missing Map");
	return (0);
}

int	parseline(char *line, t_parse *parse, t_display *display)
{
	int index;
	index = 0 + numberblank(line);
	if (line[index] == 'R')
		return (stockresolution(line + index + 1, parse, display));
	if (line[index] == 'N' && line[index + 1] == 'O')
		return (stocktextures_no(line + index + 2, display));
	if (line[index] == 'S' && line[index + 1] == 'O')
		return (stocktextures_so(line + index + 2, display));
	if (line[index] == 'W' && line[index + 1] == 'E')
		return (stocktextures_we(line + index + 2, display));
	if (line[index] == 'E' && line[index + 1] == 'A')
		return (stocktextures_ea(line + index + 2, display));
	if (line[index] == 'S' && line[index + 1] == ' ')
		return (stocktextures_s(line + index + 1, display));
	if (line[index] == 'F' && line[index + 1] == ' ')
		return (stockcolorf(line + index + 1, display));
	if (line[index] == 'C' && line[index + 1] == ' ')
		return (stockcolorc(line + index + 1, display));
	if (line[index] == '1' || line[index] == '2' || line[index] == '0')
		return (stockmap(parse, display));
	if (line[index] != '\n' && line[index] != '\0')
		showerror(display, "One or more elements in .cub are not correct");
	return (1);
}

int	checkcubextension(char *str, t_display *display)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (str[i - 1] == 'b' && str[i - 2] == 'u'
	&& str[i - 3] == 'c' && str[i - 4] == '.')
	{
		if ((i = open(str, O_RDONLY)) == -1)
			showerror(display, "File Name is not correct");
		return (1);
	}
	showerror(display, "Files without .cub extension is not accepted ");
	return (1);
}

int	initparse(t_display *display)
{
	display->mapboleen = 0;
	display->initsuccess = 0;
	display->textnum = 0;
	display->errorbool = 0;
	display->maptofree = -1;
	display->south = NULL;
	display->north = NULL;
	display->west = NULL;
	display->east = NULL;
	display->spritepwd = NULL;
	display->filename = NULL;
	return (0);
}
