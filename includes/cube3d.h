/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:50:03 by artheon           #+#    #+#             */
/*   Updated: 2025/02/19 15:20:31 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdbool.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define Z 122
# define Q 113
# define S 115
# define D 100
# define ROTATE_LEFT 65361
# define ROTATE_RIGHT 65363
# define ESC 65307
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

typedef struct s_config
{
	char	*texture_no;
	char	*texture_so;
	char	*texture_we;
	char	*texture_ea;
	int		floor_color[3];
	int		ceiling_color[3];
}	t_config;

typedef struct s_texture
{
	void	*img;
	int		*data;
	int		width;
	int		height;
}	t_texture;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_render
{
	int			x;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_index;
	t_texture	*tex;
	double		wall_x;
	int			tex_x;
	double		step;
	double		tex_pos;
	int			y;
	int			tex_y;
	int			color;
	int			floor_color;
	int			ceiling_color;
}	t_render;

typedef struct s_map_info
{
	int		num_lines;
	int		player_count;
	char	**lines;
	char	*map_section;
	int		nbrdechaines;
	int		start;
}	t_map_info;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**grid;
	int			width;
	int			height;
	int			z;
	int			s;
	int			q;
	int			d;
	int			rotate_left;
	int			rotate_right;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	t_config	*config;
	t_texture	texture[6];
	t_img		img;
	t_img		mini_map;
}	t_game;

// # ====================================================== #
// |														|
// |						utils							|
// |														|
// # ====================================================== #

void		print_char(char **split);
void		free_split(char **split);
void		error_exit(char *msg, int flags);
int			create_rgb(int r, int g, int b);
void		calculate_texture_and_draw_wall(t_render rdr, t_game *game);

// # ====================================================== #
// |														|
// |						parsing							|
// |														|
// # ====================================================== #

char		*read_file(const char *filename);
int			checking_identifier(char *line);
int			checking_identifier_args(char *line, int *count, t_config **config);
int			checking_map_element(char *line, int *count_elem, \
			t_config **config);
bool		is_valid_map_line(char *line);

// # ====================================================== #
// |														|
// |						map_parsing						|
// |														|
// # ====================================================== #

char		*check_error(char *file_content, t_config **config);
t_game		*parse_map(char *map_section, t_config *config);

// # ====================================================== #
// |														|
// |						player_setup					|
// |														|
// # ====================================================== #

void		set_north_dir(t_game *map);
void		set_south_dir(t_game *map);
void		set_east_dir(t_game *map);
void		set_west_dir(t_game *map);
void		set_player_dir(t_game *map, char dir);

// # ====================================================== #
// |														|
// |						player_setup					|
// |														|
// # ====================================================== #

void		pad_map_lines(t_game *map);

// # ====================================================== #
// |														|
// |						map_setup						|
// |														|
// # ====================================================== #

void		handle_error(t_game *map, char *msg);
void		init_player_and_check_walls(t_game *map);

// # ====================================================== #
// |														|
// |						map_validator					|
// |														|
// # ====================================================== #

t_map_info	validate_map_section(char *map_section);
int			validate_elements(char **lines, int *count_element, \
			t_config **config);
bool		is_valid_map_char(char c);
bool		is_player_char(char c);

// # ====================================================== #
// |														|
// |						texture							|
// |														|
// # ====================================================== #

void		load_texture(t_game *game, t_texture *tex, char *path);
void		load_all_texture(t_game *game);
int			get_texture_index(int side, double ray_dir_x, double ray_dir_y);

// # ====================================================== #
// |														|
// |						image							|
// |														|
// # ====================================================== #

void		init_image(t_game *game);
void		put_pixel_mini_map(t_game *game, int x, int y, int color);
void		my_mlx_pixel_put(t_game *game, int x, int y, int color);
void		clear_image(t_game *game);

// # ====================================================== #
// |														|
// |						draw							|
// |														|
// # ====================================================== #

void		draw_background(t_render rdr, t_game *game);
void		draw_minimap(t_game *game);

// # ====================================================== #
// |														|
// |						rendering						|
// |														|
// # ====================================================== #

int			render(t_game *map);

// # ====================================================== #
// |														|
// |						input							|
// |														|
// # ====================================================== #

void		forward_back(t_game *game);
void		right_left(t_game *game);
void		rotate_left(t_game *game);
void		rotate_right(t_game *game);

// # ====================================================== #
// |														|
// |						input							|
// |														|
// # ====================================================== #

void		key(t_game *game);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);

// # ====================================================== #
// |														|
// |						exit							|
// |														|
// # ====================================================== #

int			exit_game(t_game *game);

#endif