/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stockcolor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jo@cluzet.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 22:23:05 by jcluzet           #+#    #+#             */
/*   Updated: 2021/02/16 01:22:59 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	stockcolorf(char *line, t_display *display)
{
	int i;

	i = numberblank(line);
	display->rgbfloor[0] = ft_atoi(line);
	if (display->rgbfloor[0] > 255)
		showerror(display, "Color of Floor must be under 255 (RGB)");
	i += numberblank(line + i);
	if (searchcomma(line + i) == -1)
		showerror(display, "Missing first comma into Color of Floor");
	i += searchcomma(line + i);
	display->rgbfloor[1] = ft_atoi(line + i);
	if (display->rgbfloor[1] > 255)
		showerror(display, "Color of Floor must be under 255 (RGB)");
	i++;
	i += numberblank(line + i);
	if (searchcomma(line + i) == -1)
		showerror(display, "Missing second comma into Color of Floor");
	i += searchcomma(line + i);
	display->rgbfloor[2] = ft_atoi(line + i);
	if (display->rgbfloor[2] > 255)
		showerror(display, "Color of Floor must be under 255 (RGB)");
	display->textnum++;
	return (1);
}

int	stockcolorc(char *line, t_display *display)
{
	int i;

	i = numberblank(line);
	display->rgbceiling[0] = ft_atoi(line);
	if (display->rgbceiling[0] > 255)
		showerror(display, "Color of Ceiling must be under 255 (RGB)");
	i += numberblank(line + i);
	if (searchcomma(line + i) == -1)
		showerror(display, "Missing first comma into Color of Celling");
	i += searchcomma(line + i);
	display->rgbceiling[1] = ft_atoi(line + i);
	if (display->rgbceiling[1] > 255)
		showerror(display, "Color of Ceiling must be under 255 (RGB)");
	i++;
	i += numberblank(line + i);
	if (searchcomma(line + i) == -1)
		showerror(display, "Missing second comma into Color of Celling");
	i += searchcomma(line + i);
	display->rgbceiling[2] = ft_atoi(line + i);
	if (display->rgbceiling[2] > 255)
		showerror(display, "Color of Ceiling must be under 255 (RGB)");
	display->textnum++;
	return (1);
}

int	stockresolution(char *line, t_parse *parse, t_display *display)
{
	int v;
	int i;

	v = 0;
	i = numberblank(line);
	if (i < 1)
		return (showerror(display, "Wrong argument syntax for Resolution"));
	if ((parse->r1 = (atoi(line + 1))) == 0)
		return (showerror(display, "Invalid first argument for Resolution"));
	while (line[i + v] && (line[i + v] != ' '))
		v++;
	if (v < 1)
		return (showerror(display, "Wrong argument syntax for Resolution"));
	i += v;
	if ((parse->r2 = (atoi(line + i))) == 0)
		return (showerror(display, "Invalid second argument for Resolution"));
	display->textnum++;
	return (1);
}
