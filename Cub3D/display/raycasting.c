/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 18:14:15 by jcluzet           #+#    #+#             */
/*   Updated: 2024/11/05 20:21:32 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	raycasting(t_display *display) // Envoi d'un rayon a partir du joueur (pour chaque pixel de ligne vertical)
{
	display->index = display->r1 - 1;
	while (display->index > 0)
	{
		display->camerax = 2 * display->index / (double)display->r1 - 1;
		display->d.x = display->dirx + display->planex * display->camerax;
		display->d.y = display->diry + display->planey * display->camerax;
		sendrayon(display);
		display->index--;
	}
	sendrayon(display);
	return (0);
}

int	sendrayon(t_display *display) // Calcul des coordonnées de l'intersection avec la prochaine case (deltadist)
{
	display->mapi.x = floor(display->player.x);
	display->mapi.y = floor(display->player.y);
	display->deltadist.x = sqrt(1 + ((display->d.y * display->d.y) /
				(display->d.x * display->d.x)));
	display->deltadist.y = sqrt(1 + ((display->d.x * display->d.x) /
				(display->d.y * display->d.y)));
	display->stepx = (display->d.x > 0) ? 1 : -1;
	display->stepy = (display->d.y > 0) ? 1 : -1;
	if (display->d.x > 0)
		display->sidedist.x = (display->mapi.x + 1 - display->player.x)
			* display->deltadist.x;
	else
		display->sidedist.x = (display->player.x - display->mapi.x)
			* display->deltadist.x;
	if (display->d.y > 0)
		display->sidedist.y = (display->mapi.y + 1 - display->player.y)
			* display->deltadist.y;
	else
		display->sidedist.y = (display->player.y - display->mapi.y)
			* display->deltadist.y;
	findwall(display);
	return (0);
}

int	findwall(t_display *display) // Boucle sur chaque case jusqu'a trouver un mur
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (((display->sidedist.y <= 0) || ((display->sidedist.x >= 0)
						&& display->sidedist.x < display->sidedist.y)))
		{
			display->sidedist.x += display->deltadist.x;
			display->mapi.x += display->stepx;
			display->side = 0;
		}
		else
		{
			display->sidedist.y += display->deltadist.y;
			display->mapi.y += display->stepy;
			display->side = 1;
		}
		if (display->map[display->mapi.y][display->mapi.x] == '1')
			hit = 1;
	}
	findtexturenum(display);
	return (0);
}

int	findtexturenum(t_display *display) // recherche de la texture correspondante au mur trouvé
{
	if (display->side == 0)
	{
		if (display->d.x >= 0)
			display->textnum = 3;
		else
			display->textnum = 2;
	}
	else
	{
		if (display->d.y >= 0)
			display->textnum = 1;
		else
			display->textnum = 0;
	}
	showraster(display);
	return (0);
}

void clear_terminal() {
    printf("\033[H\033[J"); // Ekranı temizle ve imleci en üst sola taşı
}

// void print_all(t_display *display)
// {
// 	// double			stepdraw;
// 	// double			texpos;
// 	// int				texxwall;
// 	// int				texywall;
// 	// int				indexdey;
// 	// int				indexdex;
// 	// double			onspritex;
// 	// double			onspritey;
// 	// double			invdet;
// 	// double			transformx;
// 	// double			transformy;
// 	// int				spritescreenx;
// 	// int				spriteheight;
// 	// int				spritewidth;
// 	// int				drawstarty;
// 	// unsigned int	colorsprite;
// 	// int				drawendy;
// 	// int				drawstartx;
// 	// int				drawendx;
// 	// int				stripe;
// 	// int				texx;
// 	// int				texy;
// 	// int				y;
// 	// int				dsprite;
// 	// int				spritenumber;
// 	// int				initsuccess;
// 	// int				maptofree;
// 	// int				keyboard[100000];
// 	// int				index;
// 	// int				bpp;
// 	// int				bpp2[11];
// 	// int				s_line;
// 	// int				s_line2[11];
// 	// int				ed2[11];
// 	// int				ed;
// 	// int				startline;
// 	// int				endline;
// 	// int				side;
// 	// double			*zbuffer;
// 	// char			**map;
// 	// char			*pxl;
// 	// char			*spritenum;
// 	// char			*north;
// 	// char			*south;
// 	// char			*west;
// 	// char			*east;
// 	// char			*spritepwd;
// 	// void			*mlx_ptr;
// 	// void			*mlx_win;
// 	// void			*img;
// 	// int				r1;
// 	// int				errorbool;
// 	// int				spritecounted;
// 	// int				r2;
// 	// int				fd;
// 	// double			stepx;
// 	// double			stepy;
// 	// double			camerax;
// 	// double			rotspeed;
// 	// double			dirx;
// 	// double			wallx;
// 	// double			diry;
// 	// double			planex;
// 	// double			planey;
// 	// int				lineheight;
// 	// double			perwalldist;
// 	// double			pspeed;
// 	// int				mapx;
// 	// int				bmp;
// 	// int				mapy;
// 	// int				*spritex;
// 	// int				*spritey;
// 	// double			*spritedist;
// 	// int				numberofplayer;
// 	// int				widthtext[11];
// 	// int				heighttext[11];
// 	// void			*text_no;
// 	// void			*text_so;
// 	// char			*filename;
// 	// int				mapboleen;
// 	// void			*text_we;
// 	// void			*text_ea;
// 	// void			*sprite;
// 	// int				textnum;
// 	// char			*ptr[11];
// 	// clock_t			last_frame;
// 	// clock_t			next_frame;
// 	// unsigned int	color;
// 	// unsigned int	rgbfloor[3];
// 	// unsigned int	rgbceiling[3];
// 	// unsigned int	rgbtemp[3];
// 	// t_ray			player;
// 	// t_ray			d;
// 	// t_ray			deltadist;
// 	// t_ray			sidedist;
// 	// t_xy1			mapi;
// 	clear_terminal();
// 	printf("display->img: %p\n", display->img);
// 	printf("display->pxl: %s\n", display->pxl);
// 	printf("display->last_frame: %ld\n", display->last_frame);
// 	printf("display->next_frame: %ld\n", display->next_frame);
// 	printf("display->mlx_win: %p\n", display->mlx_win);
// 	printf("display->r1: %d\n", display->r1);
// 	printf("display->errorbool: %d\n", display->errorbool);
// 	printf("display->spritecounted: %d\n", display->spritecounted);
// 	printf("display->r2: %d\n", display->r2);
// 	printf("display->fd: %d\n", display->fd);
// 	printf("display->stepx: %f\n", display->stepx);
// 	printf("display->stepy: %f\n", display->stepy);
// 	printf("display->camerax: %f\n", display->camerax);
// 	printf("display->rotspeed: %f\n", display->rotspeed);
// 	printf("display->dirx: %f\n", display->dirx);
// 	printf("display->diry: %f\n", display->diry);
// 	printf("display->planex: %f\n", display->planex);
// 	printf("display->planey: %f\n", display->planey);
// 	printf("display->mapx: %d\n", display->mapx);
// 	printf("display->mapy: %d\n", display->mapy);
// 	printf("display->wallx: %f\n", display->wallx);
// 	printf("display->lineheight: %d\n", display->lineheight);
// 	printf("display->perwalldist: %f\n", display->perwalldist);
// 	printf("display->pspeed: %f\n", display->pspeed);
// 	printf("display->bmp: %d\n", display->bmp);
// 	printf("display->numberofplayer: %d\n", display->numberofplayer);
// 	printf("display->textnum: %d\n", display->textnum);
// 	printf("display->mapboleen: %d\n", display->mapboleen);
// 	printf("display->last_frame: %ld\n", display->last_frame);
// 	printf("display->next_frame: %ld\n", display->next_frame);
// 	printf("display->color: %u\n", display->color);
// 	printf("display->player.x: %f\n", display->player.x);
// 	printf("display->player.y: %f\n", display->player.y);
// 	printf("display->d.x: %f\n", display->d.x);
// 	printf("display->d.y: %f\n", display->d.y);
// 	printf("display->deltadist.x: %f\n", display->deltadist.x);
// 	printf("display->deltadist.y: %f\n", display->deltadist.y);
// 	printf("display->sidedist.x: %f\n", display->sidedist.x);
// 	printf("display->sidedist.y: %f\n", display->sidedist.y);
// 	printf("display->mapi.x: %d\n", display->mapi.x);
// 	printf("display->mapi.y: %d\n", display->mapi.y);
// 	printf("display->startline: %d\n", display->startline);

// }

int	showraster(t_display *display)
{

	// print_all(display);
	if (display->side == 0)                                      // Perwalldist = distance final entre le joeur et le mur trouvé (pour un rayon)
		display->perwalldist = (display->mapi.x - display->player.x +
				(1 - display->stepx) / 2) / display->d.x;
	else
		display->perwalldist = (display->mapi.y - display->player.y +
				(1 - display->stepy) / 2) / display->d.y;
	display->lineheight = (int)(display->r2 / display->perwalldist);     // Calcul de la hauteur du mur (plus perwalldist est grand, plus le mur est petit >raycasting)
	display->startline = -display->lineheight / 2 + display->r2 / 2;
	if (display->startline < 0)
		display->startline = 0;
	display->endline = display->lineheight / 2 + display->r2 / 2;
	if (display->endline >= display->r2)
		display->endline = display->r2 - 1;
	if (display->side == 0)
		display->wallx = display->player.y +
		display->perwalldist * display->d.y;
	else
		display->wallx = display->player.x +
		display->perwalldist * display->d.x;
	display->wallx -= floor((display->wallx));
	draw_line(display, display->index);
	return (1);
}
