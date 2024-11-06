/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jo@cluzet.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:25:03 by jcluzet           #+#    #+#             */
/*   Updated: 2021/02/16 01:34:17 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		put_pxl(t_display *display, int x, int y, unsigned int c)
{
	char		*dest;

	if (y >= display->r2 || x >= display->r1 || x < 0 \
	|| y < 0)
		showerror(display, "Pixel Error");
	dest = display->pxl + display->s_line * y + x * (display->bpp / 8); // Modification de la couleur de la valeur correspondante au pixel dans l'adresse mlx
	*(unsigned int *)dest = c;
	return (0);
}

int		draw_line(t_display *display, int x)
{
	int y;

	getinfowalltext(display, x);
	y = -1;
	while (++y < display->startline)   // draw du plafond en couleur rgb
		put_pxl(display, x, y,
			colortoint(display->rgbceiling[0],
			display->rgbceiling[1], display->rgbceiling[2]));
	while (y < display->endline)
	{
		display->texywall = (int)display->texpos &
		(display->heighttext[display->textnum] - 1);
		display->texpos += display->stepdraw;
		display->color = *(unsigned int *)(display->ptr[display->textnum] +         // Recuperation de la couleur de la texture correspondante (tex_x / tex_y)
		display->s_line2[display->textnum] * display->texywall +
		display->texxwall * (display->bpp2[display->textnum] / 8));
		put_pxl(display, x, y, display->color);
		y++;
	}
	y--;
	while (++y < display->r2)
		put_pxl(display, x, y,
			colortoint(display->rgbfloor[0],
			display->rgbfloor[1], display->rgbfloor[2]));
	return (0);
}

void	getinfowalltext(t_display *display, int x)
{
	display->texxwall = (int)(display->wallx *
	(double)(display->widthtext[display->textnum]));
	if (display->spritecounted > 0)
		display->zbuffer[x] = display->perwalldist;
	if (display->side == 0 && display->d.x > 0)
		display->texxwall = display->widthtext[display->textnum]
		- display->texxwall - 1;
	if (display->side == 1 && display->d.y < 0)
		display->texxwall = display->widthtext[display->textnum]
		- display->texxwall - 1;
	display->stepdraw = 1.0 * display->heighttext[display->textnum]
	/ display->lineheight;
	display->texpos = (display->startline - display->r2
	/ 2 + display->lineheight / 2) * display->stepdraw;
}
