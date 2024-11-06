/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:25:03 by jcluzet           #+#    #+#             */
/*   Updated: 2024/11/03 00:03:20 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int	main(int argc, char **argv)
{
	t_parse		parsee;
	t_display	displayy;

	initparse(&displayy);
	if (argc == 1)
		return
		(showerror(&displayy, "No path to scene file have been provided."));
	if (argc > 3)
		return
		(showerror(&displayy, "More than two argument have been provided."));
	if (argc == 3 && cmp(argv[2], "--save", 6))
		return (showerror(&displayy, "Invalid second argument"));
	parse(argc, argv[1], &parsee, &displayy);
	display(&parsee, &displayy);
	return (EXIT_SUCCESS);
}
