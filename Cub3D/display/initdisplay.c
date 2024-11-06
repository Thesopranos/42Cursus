/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initdisplay.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:25:03 by jcluzet           #+#    #+#             */
/*   Updated: 2024/11/02 21:19:10 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		display(t_parse *parse, t_display *display)
{
	initdisplay(display, parse);
	newwindow(display);
	if (display->bmp == 1)
		create_bmp(display);
	mlx_do_key_autorepeatoff(display->mlx_ptr);
	mlx_hook(display->mlx_win, 2, 1L, ft_key_hit, display);
	mlx_hook(display->mlx_win, 3, 2L, ft_key_release, display);
	mlx_hook(display->mlx_win, CLOSERED, 1L << 17, closebyredbutton, display);
	mlx_hook(display->mlx_win, 12, 0, ft_expose, display);
	mlx_loop_hook(display->mlx_ptr, key_loop, display);
	mlx_loop(display->mlx_ptr);
	return (0);
}

int		newwindow(t_display *display)
{
	display->mlx_ptr = mlx_init();
	display->img = mlx_new_image(display->mlx_ptr, display->r1, display->r2);
	display->pxl = mlx_get_data_addr(display->img,
			&(display->bpp), &(display->s_line),
			&(display->ed));
	display->last_frame = clock();
	display->next_frame = 0;
	if (display->bmp == 0)
	{
		if ((display->mlx_win = mlx_new_window(display->mlx_ptr, display->r1,
						display->r2, "42 Cub3D JCluzet")) == NULL)
			return (EXIT_FAILURE);
		else
			display->initsuccess = 1;
	}
	loadtextures(display);
	loadsprites(display);
	raycasting(display);
	if (display->bmp == 0)
		mlx_put_image_to_window(display->mlx_ptr,
			display->mlx_win, display->img, 0, 0);
	if (display->bmp == 0)
		printf("\033[0;32m[ Cub3D launched Successfully ]\n");
	return (0);
}

int		key_loop(t_display *display)
{
	ft_keyboard(display);
	if (display->keyboard[ESC] || display->keyboard[ROT_LEFT]
	|| display->keyboard[ROT_RIGHT] || display->keyboard[RIGHT]
	|| display->keyboard[LEFT] || display->keyboard[BACK]
	|| display->keyboard[ADVANCE])
		raycasting(display);
	if (display->spritecounted != 0)
		showsprite(display);
	mlx_put_image_to_window(display->mlx_ptr,
	display->mlx_win, display->img, 0, 0);
	return (0);
}

void	initdisplay(t_display *display, t_parse *parse)
{
	display->bpp = 0;
	display->s_line = 0;
	display->pspeed = 0.1;
	display->rotspeed = 0.04;
	display->index = 0;
	display->r1 = parse->r1;
	display->r2 = parse->r2;
	display->keyboard[BACK] = 0;
	display->keyboard[RED_BUTTON] = 0;
	display->keyboard[ROT_RIGHT] = 0;
	display->keyboard[ESC] = 0;
	display->keyboard[LEFT] = 0;
	display->keyboard[RIGHT] = 0;
	display->keyboard[ROT_LEFT] = 0;
	display->keyboard[ADVANCE] = 0;
}

int		ft_expose(t_display *display)
{
	mlx_put_image_to_window(display->mlx_ptr,
	display->mlx_win, display->img, 0, 0);
	return (0);
}
