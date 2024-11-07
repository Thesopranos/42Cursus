/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:58:21 by zumgenc           #+#    #+#             */
/*   Updated: 2024/11/07 19:08:25 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdbool.h>

# define WIDTH 800
# define HEIGHT 600
# define TEXWIDTH 64
# define TEXHEIGHT 64

// keycodes
# define KEY_EXIT 53
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_ESC 53

// colors
# define RED "\033[1;31m"
# define YELLOW "\033[1;33m"
# define GREEN "\033[1;32m"
# define RESET "\033[0m"

typedef struct s_image
{
	void	*image;
	int		*addr;
	int		number;
}			t_image;

typedef struct s_map
{
	char	**map;
	int		mapwidth;
	int		mapheight;
	char	*path;
	char	*direction;
	int		fd;
	int		fd_buff;

	int		realmap_height;

	int		playercount;
	char	pov;
	int		map_start;
	int		map_start_buff;
	char	*map_line;

	char	*sotexturepath;
	char	*notexturepath;
	char	*eatexturepath;
	char	*wetexturepath;

	char	**realmap;
	char	**tmp_map;
	char	**map_buff;
	int		pos_x;
	int		pos_y;

	int		fcolor;
	int		ccolor;
	int		noflag;
	int		noflag_buff;
	int		weflag;
	int		weflag_buff;
	int		eaflag;
	int		eaflag_buff;
	int		soflag;
	int		soflag_buff;
	int		cflag;
	int		cflag_buff;
	int		fflag;
	int		fflag_buff;
	int		flagcount;
	int		flagcount_buff;
	int		if_flag_buff;
	int		if_flag;
	int		buff_endofflag;
}			t_map;

typedef struct s_game
{
	void	*mlx;
	void	*mlxwin;
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	camerax;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	double	wallx;
	double	raydirx;
	double	raydiry;
	double	step;
	double	texpos;
	int		color;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineh;
	int		drawstart;
	int		drawend;
	int		texx;
	int		texy;
	int		texh;
	int		texw;
	bool	w;
	bool	s;
	bool	a;
	bool	d;
	bool	left;
	bool	right;
	float	speed;
	float	rspeed;
	t_image	*no;
	t_image	*so;
	t_image	*we;
	t_image	*ea;
	t_image	*image;
	t_map	*map;
}			t_game;

int			ft_err(char *str, t_game *game, int status);
void		map_control(t_map *map);
int			map_so_control(t_map *map, int i);
int			map_so_control_buff(t_map *map, int i);
int			map_no_control(t_map *map, int i);
int			map_no_control_buff(t_map *map, int i);
int			map_ea_control(t_map *map, int i);
int			map_ea_control_buff(t_map *map, int i);
int			map_we_control(t_map *map, int i);
int			map_we_control_buff(t_map *map, int i);
int			map_f_control(t_map *map, int i);
int			map_f_control_buff(t_map *map, int i);
int			map_c_control(t_map *map, int i);
int			map_c_control_buff(t_map *map, int i);
char		*get_next_line(int fd);
void		err_print_exit(char *str);
void		*myfree(void **str);
char		*texture_path_handler(char *str);
int			newline_control(t_map *map, int i);
int			space_control(t_map *map, int i);
char		*color_path_handler(char *str);
int			check_line_dir(char *map);
int			map_sixthcontrol(t_map *map);
void		mapread(t_map *map);
int			ft_err_mapcontrol(char *str, t_map *map, int status);
void		free_map(t_map *map);
void		map_size(t_map *map);
int			take_rgb_color(char *str, t_map *map);
void		is_digit_color(char *tmp, char **str, t_map *map);
void		free_array2d(char **str);
void		create_tmp_map(t_map *map);
void		func(t_map *map);
void		func2(t_map *map);
int			count_comma(char *str);
void		movement_2(t_game *game);
void		movement_(t_game *game);
void		find_hight_real_map(t_map *map);
void		check_real_map(t_map *map);
void		check_real_map_counts(t_map *map);
void		create_tmp_map(t_map *map);
void		read_real_map(t_map *map);
void		skip_spaces2(t_map *map, int end);
void		skip_spaces(t_map *map, int end);
void		ray_init(t_game *game);
void		ft_mlx(t_game *g, int a, int b);
int			move_press(int keyCode, t_game *game);
int			move_release(int keyCode, t_game *game);
int			gamefunc(t_game *game);
void		render_column(t_game *game, int x, int y);
void		calculate_wall_height(t_game *game);
void		calculate_hit_distance(t_game *game);
void		calculate_ray(t_game *game, int x);
void		calculate_step(t_game *g);
void		calculate_wall_height_x(t_game *game);
void		calculate_wall_height_y(t_game *game);
int			ft_skip_spaces(char *str, int i);

// dev tools
void		print_map_attr(t_map *map);

#endif
