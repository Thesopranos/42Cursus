/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stocktexture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jo@cluzet.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 22:23:05 by jcluzet           #+#    #+#             */
/*   Updated: 2021/02/14 16:04:31 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	stocktextures_no(char *line, t_display *display)
{
	int i;
	int l;

	i = numberblank(line);
	l = 0;
	if (display->north != NULL)
		showerror(display, "Texture NO is duplicated");
	if (((display->north = malloc(sizeof(char)
	* strlentoend(line + i) + 1))) == NULL)
		showerror(display, "Unable to Malloc");
	if ((open(line + i, O_RDONLY) == -1))
		showerror(display, "Texture NO not existing");
	while (isend(line + i + l) == 0 && line[i + l])
	{
		display->north[l] = line[i + l];
		l++;
	}
	display->north[l] = '\0';
	display->textnum++;
	return (1);
}

int	stocktextures_so(char *line, t_display *display)
{
	int i;
	int l;

	i = numberblank(line);
	l = 0;
	if (display->south != NULL)
		showerror(display, "Texture SO is duplicated");
	if ((open(line + i, O_RDONLY) == -1))
		showerror(display, "Texture SO not existing");
	if (((display->south = malloc(sizeof(char)
	* strlentoend(line + i) + 1))) == 0)
		showerror(display, "Unable to Malloc");
	while (isend(line + i + l) == 0 && line[i + l])
	{
		display->south[l] = line[i + l];
		l++;
	}
	display->south[l] = '\0';
	display->textnum++;
	return (1);
}

int	stocktextures_we(char *line, t_display *display)
{
	int i;
	int l;

	i = numberblank(line);
	l = 0;
	if (display->west != NULL)
		showerror(display, "Texture WE is duplicated");
	if ((open(line + i, O_RDONLY) == -1))
		showerror(display, "Texture WE not existing");
	if (((display->west = malloc(sizeof(char)
	* strlentoend(line + i) + 1))) == 0)
		showerror(display, "Unable to Malloc");
	while (isend(line + i + l) == 0 && line[i + l])
	{
		display->west[l] = line[i + l];
		l++;
	}
	display->west[l] = '\0';
	display->textnum++;
	return (1);
}

int	stocktextures_ea(char *line, t_display *display)
{
	int i;
	int l;

	i = numberblank(line);
	l = 0;
	if (display->east != NULL)
		showerror(display, "Texture EA is duplicated");
	if ((open(line + i, O_RDONLY) == -1))
		showerror(display, "Texture EA not existing");
	if (((display->east = malloc(sizeof(char)
	* strlentoend(line + i) + 1))) == 0)
		showerror(display, "Unable to Malloc");
	while (isend(line + i + l) == 0 && line[i + l])
	{
		display->east[l] = line[i + l];
		l++;
	}
	display->east[l] = '\0';
	display->textnum++;
	return (1);
}

int	stocktextures_s(char *line, t_display *display)
{
	int i;
	int l;

	i = numberblank(line);
	l = 0;
	if (display->spritepwd != NULL)
		showerror(display, "Texture S is duplicated");
	if ((open(line + i, O_RDONLY) == -1))
		showerror(display, "Texture Sprite not existing");
	if (((display->spritepwd = malloc(sizeof(char)
	* strlentoend(line + i) + 1))) == 0)
		showerror(display, "Unable to Malloc");
	while (isend(line + i + l) == 0 && line[i + l])
	{
		display->spritepwd[l] = line[i + l];
		l++;
	}
	display->spritepwd[l] = '\0';
	display->textnum++;
	return (1);
}
