/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:37:32 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/11 17:36:57 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# define WIDTH 800
# define HEIGHT 600
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define KEY_EXIT 53
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_ESC 53
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

typedef struct s_flags
{
	int		no_flag;
	int		we_flag;
	int		ea_flag;
	int		so_flag;
	int		c_flag;
	int		f_flag;
	int		flag_count;
	int		if_flag;
}			t_flags;

typedef struct s_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	bool	w;
	bool	s;
	bool	a;
	bool	d;
	bool	left;
	bool	right;
	float	player_speed;
	float	rot_speed;
}			t_player;

typedef struct s_map
{
	char	**map_file;
	int		map_file_height;
	char	*map_file_path;
	int		map_file_fd;
	int		map_height;
	int		player_count;
	char	direction;
	int		map_start;
	char	*one_line_map;
	char	*so_tex_path;
	char	*no_tex_path;
	char	*ea_tex_path;
	char	*we_tex_path;
	char	**map;
	char	**tmp_map;
	char	**map_buff;
	int		pos_x;
	int		pos_y;
	int		f_color;
	int		c_color;
	t_flags	*flags;
	t_flags	*buff_flags;
	int		buff_endofflag;
}			t_map;

typedef struct s_ray
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	double	wallx;
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
	double	texpos;
}			t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*mlxwin;
	double		planex;
	double		planey;
	double		step;
	int			color;
	t_ray		*ray;
	t_player	*p;
	t_image		*no;
	t_image		*so;
	t_image		*we;
	t_image		*ea;
	t_image		*image;
	t_map		*map;
}				t_game;

int				ft_err(char *str, t_game *game, int status);
void			map_control(t_map *map);
int				map_so_control(t_map *map, int i);
int				map_so_control_buff(t_map *map, int i);
int				map_no_control(t_map *map, int i);
int				map_no_control_buff(t_map *map, int i);
int				map_ea_control(t_map *map, int i);
int				map_ea_control_buff(t_map *map, int i);
int				map_we_control(t_map *map, int i);
int				map_we_control_buff(t_map *map, int i);
int				map_f_control(t_map *map, int i);
int				map_f_control_buff(t_map *map, int i);
int				map_c_control(t_map *map, int i);
int				map_c_control_buff(t_map *map, int i);
char			*get_next_line(int fd);
void			err_print_exit(char *str);
char			*texture_path_handler(char *str);
int				newline_control(t_map *map, int i);
int				space_control(t_map *map, int i);
char			*color_path_handler(char *str);
int				check_line_dir(char *map);
int				map_sixthcontrol(t_map *map);
void			mapread(t_map *map);
int				ft_err_mapcontrol(char *str, t_map *map, int status);
void			free_map(t_map *map);
void			map_size(t_map *map);
int				take_rgb_color(char *str, t_map *map);
void			is_digit_color(char *tmp, char **str, t_map *map);
void			free_array2d(char **str);
void			create_tmp_map(t_map *map);
void			func(t_map *map);
void			func2(t_map *map);
int				count_comma(char *str);
void			movement_2(t_game *game);
void			find_height_real_map(t_map *map);
void			check_real_map(t_map *map);
void			check_real_map_counts(t_map *map);
void			create_tmp_map(t_map *map);
void			read_real_map(t_map *map);
void			skip_spaces(t_map *map, int end);
void			ray_init(t_game *game);
void			ft_mlx(t_game *g, int a, int b);
int				move_press(int keyCode, t_game *game);
int				move_release(int keyCode, t_game *game);
int				gamefunc(t_game *game);
void			render_column(t_game *game, int x, int y);
void			calculate_wall_height(t_game *game);
void			calculate_hit_distance(t_game *game);
void			calculate_ray(t_game *game, int x);
void			calculate_step(t_game *g);
void			calculate_wall_height_x(t_game *game);
void			calculate_wall_height_y(t_game *game);
int				ft_skip_spaces(char *str, int i);
int				all_spaces(char *str);
int				exit_mlx(t_game *game);
void			rotate2(t_game *g, double dir, double plane);
int				is_valid_file(char *path);
int				skip_first_spaces(char *str);
void			copy_string(char *ret_path, const char *str);
char			**ft_adv_split(char const *s, char c, int *split_status);
unsigned int	ft_charlen(const char *s, char c);

#endif
