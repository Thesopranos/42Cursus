/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   madebmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jo@cluzet.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:25:03 by jcluzet           #+#    #+#             */
/*   Updated: 2021/02/06 00:43:43 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		create_bmp(t_display *display)
{
	int				fd;
	t_bmp_h			head;

	if ((fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666)) < 0)
		return (showerror(display, "Could not create .bmp file\n"));
	head = set_bmp_header(display);
	if (write(fd, "BM", 2) < 2
	|| write(fd, &head, sizeof(head)) < (long)sizeof(head))
		return (showerror(display, "Could not write in .bmp file\n"));
	write_bmp_image(display, fd);
	close(fd);
	display->errorbool = 1;
	printf("\033[0;32m[ BMP Successfully created ]\n");
	freeandexit(display);
	return (0);
}

int		write_bmp_image(t_display *display, int fd)
{
	void			*addr;
	char			buffer[display->s_line];
	int				i;

	i = 0;
	addr = draw_image(display);
	while (i < display->r2)
	{
		ft_memcpy(buffer, addr + display->s_line *
		(display->r2 - i - 1), display->s_line);
		if (write(fd, &buffer, display->s_line) < display->s_line)
			return (showerror(display, "Could not complete write the image\n"));
		++i;
	}
	return (0);
}

void	*draw_image(t_display *display)
{
	clear_img_buffer(display);
	raycasting(display);
	return (display->pxl);
}

t_bmp_h	set_bmp_header(t_display *display)
{
	t_bmp_h			head;

	head.file_size = (display->r1 * display->r2 * (display->bpp / 8)) + 54;
	head.reserved = 0;
	head.offset = 54;
	head.head_size = 40;
	head.width = display->r1;
	head.height = display->r2;
	head.planes = 1;
	head.bpp = display->bpp;
	head.compression = 0;
	head.img_size = display->r1 * display->r2 * (display->bpp / 8);
	head.x_res = 0;
	head.y_res = 0;
	head.color_palette = 0;
	head.color_prio = 0;
	return (head);
}
