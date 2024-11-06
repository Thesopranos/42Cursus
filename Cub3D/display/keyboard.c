/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 19:54:37 by jcluzet           #+#    #+#             */
/*   Updated: 2024/11/03 00:27:26 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_key_hit(int keycode, t_display *display)
{
	display->keyboard[keycode] = 1;
	return (0);
}

int		ft_key_release(int keycode, t_display *display)
{
	display->keyboard[keycode] = 0;
	return (0);
}

int		ft_keyboard(t_display *display)
{
	if (display->keyboard[ADVANCE])
		moveplayer(1, display);
	if (display->keyboard[BACK])
		moveplayer(-1, display);
	if (display->keyboard[LEFT])
		moveplayer(2, display);
	if (display->keyboard[RIGHT])
		moveplayer(3, display);
	if (display->keyboard[ROT_RIGHT])
		rotation(-1, display);
	if (display->keyboard[ROT_LEFT])
		rotation(1, display);
	if (display->keyboard[ESC] || display->keyboard[RED_BUTTON])
	{
		printf("%d\n", display->index);
		freeandexit(display);
	}
	return (0);
}

int		closebyredbutton(t_display *display)
{
	display->keyboard[RED_BUTTON] = 1;
	return (0);
}
