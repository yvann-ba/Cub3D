/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:49:18 by lauger            #+#    #+#             */
/*   Updated: 2024/10/15 15:03:23 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define BUFFER_SIZE 1024
# define MAX_RGB 255

# define SCREEN_WIDTH 896
# define SCREEN_HEIGHT 512

# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define MAGENTA	"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"
# include <time.h>
# include <sys/time.h>
# include "../Libft/libft.h"
# include <math.h>

typedef struct s_ray		t_ray;
typedef struct s_data		t_data;
typedef struct s_read_file	t_read_file;

typedef struct s_read_file
{
	t_data				*data;
	char				**tab_content;
	char				buffer[BUFFER_SIZE];
	char				*str_content;
	ssize_t				bytes_read;
	size_t				total_size;
	size_t				new_size;
	char				*p_north;
	char				*p_south;
	char				*p_west;
	char				*p_east;
}	t_read_file;

typedef struct s_rgb
{
	unsigned int		red;
	unsigned int		green;
	unsigned int		blue;
}	t_rgb;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_ray
{
	void				*mlx;
	void				*mlx_win;
	void				*img;
	char				*addr;
	int					bpp;
	int					size_line;
	int					endian;
	int					**int_map;
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				camera_x;
	double				ray_dir_x;
	double				ray_dir_y;
	double				time;
	double				old_time;
	int					map_x;
	int					map_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	int					hit;
	int					side;
	int					line_height;
	int					draw_start;
	int					draw_end;
	double				move_speed;
	double				rot_speed;
	double				frame_time;
	int					tex_x;
	double				wall_x;
	t_texture			*tx;
	t_texture			*tx_north;
	t_texture			*tx_south;
	t_texture			*tx_west;
	t_texture			*tx_east;
	t_data				*data;
	int					wall_color;
}	t_ray;

typedef struct s_data
{
	void				*north;
	void				*south;
	void				*west;
	void				*east;
	int					size_image;
	t_rgb				*f_int_rgb;
	t_rgb				*c_int_rgb;
	long long int		f_hex_rgb;
	long long int		c_hex_rgb;
	int					fd_file;
	char				**map;
	int					map_width;
	int					map_height;
	t_read_file			*rf;
	t_ray				*ray;
}	t_data;

int			open_file(char *file, t_data *data);
bool		has_extension(char *filename, char *extension);
t_read_file	*read_file_to_string(int fd, t_data *data);
int			check_path(t_read_file *rf, int num_line, char *id);
int			contains_only_these_characters(char **map);
void		string_to_tab(t_read_file *rf);
void		free_img_mlx_error(t_ray *ray, t_data *data);
void		grab_data(t_data *data);
int			check_line(t_read_file *rf, char *id, int num_line,
				int value_check);
int			is_in_range(int nb[6], int start, int end);
void		grab_color(t_data *data);
void		grab_map(t_data *data);
int			replace_space_to_wall(t_data *data);
int			flood_fill(char **c_map, int pos_x, int pos_y);
void		manage_utilization_flood_fill(t_data *data, char **c_map);
void		pars_clean_exit(t_data *data);
void		pars_clean_return(t_data *data);
int			clean_close_windows(void *param);
int			open_textures_paths(t_data *data, char **c_map);
int			take_colors_value(t_read_file *rf, int p_floor, int p_ceiling);
char		*deblank(char *input, int state);
void		init_ray(t_ray *ray, t_data *data, int **int_map);
void		paths_to_mlx_image_second_part(t_ray *r, t_data *data);
int			setup_mlx(t_ray *ray);
int			clean_close_windows(void *param);
void		paths_to_mlx_image(t_ray *ray, t_data *data);
void		pars_clean_exit(t_data *data);
void		pars_clean_return(t_data *data);
void		all_clean_exit(t_data *data);
void		calculate_ray(t_ray *ray, int *x);
int			render_next_frame(t_ray *ray);
void		assign_dir_tx(t_ray *ray);
void		assign_calculate_ray(t_ray *ray, int *i);
void		fill_floor_cell(t_ray *ray, int *i, int *x);
void		draw_texture(t_ray *ray, int *x);
void		texture_calculations(t_ray *ray);
long		get_current_time_millis(void);
int			**allocate_int_map(t_data *data);
void		rotate_1(int keycode, t_ray *ray);
void		move_player(int keycode, t_ray *ray);
void		move_player_x(int keycode, t_ray *ray);
void		move_player_y(int keycode, t_ray *ray);
void		set_player_position(t_ray *ray, int x, int y, char direction);
void		parse_map(t_ray *ray, t_data *data, int **int_map);
int			key_hook(int keycode, t_ray *ray);

#endif
