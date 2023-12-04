/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <kaoel-yo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:10:24 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/12/02 09:27:55 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/******************************INCLUDES******************************/
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/******************************DEFINES******************************/
# define TILE_SIZE 48
# define MOVE_SPEED 5
# define ROT_SPEED 0.1
# define FOV 1.0472
# define PI 3.14159265359
# define WI 1200
# define HE 800
# define SOUTH 0
# define NORTH 1
# define EAST 2
# define WEST 3

/******************************STRUCTS******************************/
typedef struct s_data
{
	char		fov;
	int			nop;
	int			pop_x;
	int			pop_y;
	char		**file1;
	char		*file;
	char		**m;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	int			floor_r;
	int			floor_g;
	int			floor_b;
	int			ceiling_r;
	int			ceiling_g;
	int			ceiling_b;
	int			count;
}				t_data;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_player
{
	double		fov;
	double		a_slide;
	double		pos_x;
	double		pos_y;
}				t_player;

typedef struct s_ray
{
	double		angle;
	double		h_x;
	double		h_y;
	double		v_x;
	double		v_y;
	double		h_dist;
	double		v_dist;
	double		dist;
	double		hit_x;
	double		hit_y;
	int			color;
	int			is_vertical;
	int			is_horizontal;
}				t_ray;

typedef struct s_walls
{
	double		wall_height;
	double		wall_top;
	double		wall_bottom;
	int			walltp;
	int			x;
}				t_walls;

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_texture;

typedef struct s_index
{
	int			y1;
	int			y2;
}				t_index;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
	int			width;
	int			height;
	char		**map;
	t_img		img;
	t_data		*data;
	t_player	player;
	t_texture	*textures;
	int			floor_color;
	int			ceiling_color;
}				t_mlx;

/******************************FPROTOTYPES******************************/
/********************************PARSING*******************************/
/*check_color.c*/
int				is_all_digits(char *str);
int				invalid_rgb(char **line);
int				invalid_cf_line(char *line);
void			check_floor(char *line, t_data *data);
void			check_ceiling(char *line, t_data *data);
/*check_map_tools.c*/
int				check_characters(t_data *data);
int				check_the_wall(t_data *data);
int				is_map(char *str);
void			check_new_line(char *str);
/*check_map.c*/
int				get_max_len(char **map);
void			fill_map(char **map, t_data *data);
void			get_player_position(t_data *data);
int				check_direction(char *line, t_data *data);
void			check_map(char **map, t_data *data);
/*check_textures.c*/
void			check_north(char *line, t_data *data);
void			check_south(char *line, t_data *data);
void			check_west(char *line, t_data *data);
void			check_east(char *line, t_data *data);
void			check_lines(t_data *data);
/*ft_init.c*/
void			ft_init_data(t_data *data);
/*parsing_utils.c*/
void			print_error(char *str);
void			print_exit(char *str);
void			free_array(char **array);
int				ft_array_length(char **array);
int				count_comma(char *str);
/*read_the_file.c*/
int				check_arg(char **argv);
char			*read_file(char **argv);
int				check_input(int argc, char **argv);
t_data			*parsing(int argc, char **argv);

/******************************RAYCASTING******************************/
/*textures.c*/
int				get_x_offset(t_ray *ray, int texture_width);
int				set_textures_direction(t_ray *ray);
int				fill_texture(t_mlx *game, t_texture *texture, char *path);
int				init_textures(t_mlx *game);
void			draw_line(t_mlx *game, int x, t_index index, int color);
/*raycasting.c*/
void			raycasting(t_mlx *game);
void			draw_wall(t_mlx *game, t_ray *ray, int x);
void			create_starfield(t_mlx *game, int x, int start, int end);
int				get_pixel_color(t_texture texture, int x, int y);
void			draw_texture(t_mlx *game, t_ray *ray, t_walls wall,
					t_texture texture);
/*dda.c*/
t_ray			*help_horizontal(t_mlx *game, t_ray *ray, double *x, double *y);
void			horizontal_intersection(t_mlx *game, t_ray *ray);
t_ray			*help_vertical(t_mlx *game, t_ray *ray, double *x, double *y);
void			vertical_intersection(t_mlx *game, t_ray *ray);
t_ray			get_distance(t_mlx *game, t_ray ray);
/*events.c*/
void			w_key(t_mlx *game);
void			s_key(t_mlx *game);
void			a_key(t_mlx *game);
void			d_key(t_mlx *game);
void			rotation_keys(t_mlx *game, int keycode);
/*hook.c*/
int				key_press(int keycode, t_mlx *game);
int				cross_button(t_mlx *game);
int				check_colision(t_mlx *game, double new_x, double new_y,
					int key);
/*start.c*/
t_mlx			*init_game(t_mlx *game, int argc, char **argv);
void			my_mlx_put_pixel(t_img *img, int x, int y, int color);
double			get_player_angle(t_mlx *game);
void			display_3d(t_mlx *game);
int				create_rgb(int r, int g, int b);
/******************************MAIN******************************/
/*cub3d.c*/

#endif
