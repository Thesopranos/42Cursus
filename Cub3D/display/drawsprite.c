/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawsprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jo@cluzet.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:25:03 by jcluzet           #+#    #+#             */
/*   Updated: 2021/02/11 14:24:48 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	getspriteinfo(t_display *display, int index)
{
	display->onspritex = display->spritex[index] - display->player.x + 0.5;
	display->onspritey = display->spritey[index] - display->player.y + 0.5;
	display->invdet = 1.0 / (display->planex * display->diry
	- display->dirx * display->planey);
	display->transformx = display->invdet *
	(display->diry * display->onspritex - display->dirx * display->onspritey);
	display->transformy = display->invdet * (-display->planey *
	display->onspritex + display->planex * display->onspritey);
	display->spritescreenx = (int)((display->r1 / 2)
	* (1 + display->transformx / display->transformy));
	display->spriteheight = abs((int)(display->r2 / (display->transformy)));
	display->spritewidth = abs((int)(display->r2 / (display->transformy)));
}

void	getxandyofsprite(t_display *display)
{
	display->drawstarty = -display->spriteheight / 2 + display->r2 / 2;
	if (display->drawstarty < 0)
		display->drawstarty = 0;
	display->drawendy = display->spriteheight / 2 + display->r2 / 2;
	if (display->drawendy >= display->r2)
		display->drawendy = display->r2 - 1;
	display->drawstartx = -display->spritewidth / 2 + display->spritescreenx;
	if (display->drawstartx < 0)
		display->drawstartx = 0;
	display->drawendx = display->spritewidth / 2 + display->spritescreenx;
	if (display->drawendx >= display->r1)
		display->drawendx = display->r1 - 1;
}

void	printsprite(t_display *display)
{
	display->y = display->drawstarty;
	while (display->y < display->drawendy)
	{
		display->dsprite = display->y * 256 - display->r2
		* 128 + display->spriteheight * 128;
		display->texy = ((display->dsprite *
		display->heighttext[5])
		/ display->spriteheight) / 256;
		display->colorsprite = *(unsigned int*)
		(display->ptr[5]
		+ display->s_line2[5]
		* display->texy + display->texx *
		(display->bpp2[5] / 8));
		if ((display->colorsprite & 0x00FFFFFF) != 0 &&
		display->y < display->r2 && display->stripe < display->r1)
			put_pxl(display, display->stripe, display->y, display->colorsprite);
		display->y++;
	}
}

void	showsprite(t_display *display)
{
	int index;

	index = 0;
	sortsprites(display);
	while (index < display->spritecounted)
	{
		getspriteinfo(display, index);
		getxandyofsprite(display);
		display->stripe = display->drawstartx;
		while (display->stripe < display->drawendx)
		{
			display->texx = (int)(256 * (display->stripe -
			(-display->spritewidth / 2 + display->spritescreenx)) *
			display->widthtext[5]
			/ display->spritewidth) / 256;
			if (display->transformy > 0.1 && display->stripe > 0
			&& display->stripe < display->r1
			&& display->transformy < display->zbuffer[display->stripe])
				printsprite(display);
			display->stripe++;
		}
		index++;
	}
}

void	sortsprites(t_display *display)
{
	int index;

	index = 0;
	while (index < display->spritecounted)
	{
		display->spritedist[index] = ((display->player.x -
		display->spritex[index]) *
		(display->player.x - display->spritex[index]) +
		(display->player.y - display->spritey[index]) *
		(display->player.y - display->spritey[index]));
		index++;
	}
	index = 1;
	while (index < display->spritecounted)
	{
		if (display->spritedist[index - 1] < display->spritedist[index])
			index = switchspriteforsort(display, index);
		index++;
	}
}
