/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeandexit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jo@cluzet.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 22:50:21 by jcluzet           #+#    #+#             */
/*   Updated: 2021/02/06 00:43:59 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			showerror(t_display *display, char *str)
{
	printf("\033[31mError\n");
	printf("\033[0;37m%s\n", str);
	display->errorbool = 1;
	freeandexit(display);
	return (0);
}

int			freeandexit(t_display *display)
{
	if (display->initsuccess == 1)
		mlx_destroy_window(display->mlx_ptr, display->mlx_win);
	freemap(display);
	if (display->south)
		free(display->south);
	if (display->north)
		free(display->north);
	if (display->west)
		free(display->west);
	if (display->east)
		free(display->east);
	if (display->spritepwd)
		free(display->spritepwd);
	if (display->filename)
		free(display->filename);
	if (display->errorbool == 0)
		printf("\n\033[31m[ Cub3D closed Successfully ]\n");
	exit(0);
}

int			freemap(t_display *display)
{
	int i;

	i = 0;
	if (display->maptofree == -1)
		return (1);
	while (i < display->maptofree)
	{
		free(display->map[i]);
		i++;
	}
	if (display->map)
		free(display->map);
	return (1);
}

void		clear_img_buffer(t_display *display)
{
	int				i;
	int				j;
	int				height;
	int				width;

	width = display->r1;
	height = display->r2;
	i = 0;
	j = 0;
	while (j < height)
	{
		while (i < width)
		{
			put_pxl(display, i, j, 0x000000);
			++i;
		}
		i = 0;
		++j;
	}
}
