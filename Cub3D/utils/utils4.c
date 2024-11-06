/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 22:50:21 by jcluzet           #+#    #+#             */
/*   Updated: 2024/11/05 22:02:28 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			ft_putstr(char *str)
{
	write(1, str, ft_strlenght(str));
}

int				cmp(char *s1, char *s2, size_t n)
{
	size_t			i;

	i = 0;
	if (!n)
		return (1);
	while (i <= 6)
	{
		if (s1[i] != s2[i])
			return (1);
		++i;
	}
	return (0);
}

int				replacecharinmap(t_display *display, char *line, int i, int len)
{
	if (line[i] == '0')
		display->map[len][i] = '9';
	if (line[i] == '2')
		display->map[len][i] = 's';
	if (line[i] == 'N')
		display->map[len][i] = initposplayer('N', len, i, display);
	if (line[i] == 'S')
		display->map[len][i] = initposplayer('S', len, i, display);
	if (line[i] == 'E')
		display->map[len][i] = initposplayer('E', len, i, display);
	if (line[i] == 'W')
		display->map[len][i] = initposplayer('W', len, i, display);
	if (line[i] == ' ')
		display->map[len][i] = 'x';
	if (checkifgood2(line[i]) == 0)
		showerror(display, "Map contain wrong character");
	return (0);
}
