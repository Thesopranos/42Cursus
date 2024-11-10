/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:45:26 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/10 15:45:27 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

void	rotate2(t_game *g, double dir, double plane)
{
	if (g->p->left)
	{
		dir = g->p->dirx;
		g->p->dirx = g->p->dirx * cos(g->p->rot_speed)
			+ g->p->diry * sin(g->p->rot_speed);
		g->p->diry = -dir * sin(g->p->rot_speed)
			+ g->p->diry * cos(g->p->rot_speed);
		plane = g->planex;
		g->planex = g->planex * cos(g->p->rot_speed)
			+ g->planey * sin(g->p->rot_speed);
		g->planey = -plane * sin(g->p->rot_speed)
			+ g->planey * cos(g->p->rot_speed);
	}
}
