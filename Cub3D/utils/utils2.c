/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 22:50:21 by jcluzet           #+#    #+#             */
/*   Updated: 2024/11/05 21:55:44 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int				ft_strlenght(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int				arrondi(int number, int boleen)
{
	int index;

	index = 0;
	while (number > index)
		index++;
	if (boleen == 1)
		return (index);
	return (index - 1);
}

unsigned int	colortoint(unsigned int r, unsigned int g, unsigned int b)
{
	unsigned int	color;

	color = r << 16 | g << 8 | b;
	return (color);
}

void print_map(t_display *display)
{
	int i, j;
	printf("Map size : %d x %d\n", display->mapx, display->mapy);
	for (i = 0; i < display->mapy; i++)
	{
		for (j = 0; j < display->mapx; j++)
		{
			printf("%c", display->map[i][j]);
		}
		printf("\n");
	}
}
void reverse_line(char *line)
{
	int i;
	char temp;

	printf("old line : %s\n", line);

	i = 0;
	while (i < ft_strlenght(line) / 2)
	{
		temp = line[i];
		line[i] = line[ft_strlenght(line) - i - 1];
		line[ft_strlenght(line) - i - 1] = temp;
		i++;
	}


	printf("new line : %s\n", line);
}



