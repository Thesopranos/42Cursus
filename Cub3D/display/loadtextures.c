/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadtextures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:25:03 by jcluzet           #+#    #+#             */
/*   Updated: 2024/11/03 14:17:48 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	loadtextures(t_display *display)
{
	if ((display->text_no = mlx_xpm_file_to_image(display->mlx_ptr,
	display->north, &display->widthtext[0], &display->heighttext[0])))
		display->ptr[0] = mlx_get_data_addr(display->text_no,
		&(display->bpp2[0]), &(display->s_line2[0]), &(display->ed2[0]));
	if ((display->text_so = mlx_xpm_file_to_image(display->mlx_ptr,
	display->south, &display->widthtext[1], &display->heighttext[1])))
		display->ptr[1] = mlx_get_data_addr(display->text_so,
		&(display->bpp2[1]), &(display->s_line2[1]), &(display->ed2[1]));
	if ((display->text_we = mlx_xpm_file_to_image(display->mlx_ptr,
	display->west, &display->widthtext[2], &display->heighttext[2])))
		display->ptr[2] = mlx_get_data_addr(display->text_we,
		&(display->bpp2[2]), &(display->s_line2[2]), &(display->ed2[2]));
	if ((display->text_ea = mlx_xpm_file_to_image(display->mlx_ptr,
	display->east, &display->widthtext[3], &display->heighttext[3])))
		display->ptr[3] = mlx_get_data_addr(display->text_ea,
		&(display->bpp2[3]), &(display->s_line2[3]), &(display->ed2[3]));
	checksizetext(display);
}

void	checksizetext(t_display *display)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (display->widthtext[i] > 64 || display->heighttext[i] > 64)
			showerror(display, "Wall textures max is 64 x 64 pixels");
		i++;
	}
}
