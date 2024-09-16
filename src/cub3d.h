#ifndef CUB3D_H
# define CUB3D_H

# define BUFFER_SIZE 1024
# define MAX_RGB 255

//COLORS
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

typedef struct s_ray t_ray;
typedef struct s_data t_data;
typedef struct s_read_file t_read_file;

typedef struct s_read_file
{
	t_data		*data;
	char		**tab_content;
	char		buffer[BUFFER_SIZE];
	char		*str_content;
	ssize_t		bytes_read;
	size_t		total_size;
	size_t		new_size;
	char		*p_north;
	char		*p_south;
	char		*p_west;
	char		*p_east;
} t_read_file;

typedef struct s_rgb
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
} t_rgb;


// RAYCASTING & GRAPHICS
typedef struct s_ray
{
	void        *mlx;
	void        *mlx_win;
	void        *img;
	int         *addr;
	int         bpp;
	int         line_length;
	int         endian;

	int     **int_map;
	int     screen_width;
	int     screen_height;
	int		screen_half_width;
	int		screen_half_height;
	int		render_delay;
	double	player_fov;
	double	player_half_fov;
	double	ray_increment_angle;
	int		raycasting_precision;
	int		**map;
	double	player_angle;
	double	pos_x;
	double	pos_y;
	double  dir_x;
	double  dir_y;
	double  plane_x;
	double  plane_y;
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	double  time;
	double  old_time;
	int     map_x;
	int     map_y;
	double  side_dist_x;
	double  side_dist_y;
	double  delta_dist_x;
	double  delta_dist_y;
	double  perp_wall_dist;
	int     step_x;
	int     step_y;
	int     hit;
	int     side;
	int     line_height;
	int     draw_start;
	int     draw_end;
	double  move_speed;
	double  rot_speed;
	double  frame_time;
	t_data	*data;

} t_ray;

typedef struct s_data
{
	void		*north;
	void		*south;
	void		*west;
	void		*east;
	int			size_image;
	t_rgb		*f_rgb;
	t_rgb		*c_rgb;
	int			fd_map;
	char**		map;
	int			map_width;
	int			map_height;
	t_read_file	*read_file;
	t_ray		*ray;
} t_data;

//--------------------------------------------LILIEN

//open_file_check_format.c
int			open_file(char *file, t_data *data);
bool		has_extenssion(char *filename, char *extenssion);

//file_to_string.c
t_read_file	*read_file_to_string(int fd, t_data *data);

//string_to_tab.c
void		string_to_tab(t_read_file *rf);

//grab_file_data.c
void		grab_data(t_data *data);
int			check_line(t_read_file *rf, char *id, int num_line, int value_check);

//grab_file_data_color.c
void		grab_color(t_data *data);

//grab_file_data_map.c
void		grab_map(t_data *data);

//flood_fill.c
int			replace_space_to_wall(t_data *data);
int			flood_fill(char **c_map, int pos_x, int pos_y);

//TEMPOARY FUNCTIONS
void    print_2d_array(char **array, int rows);

//CLEAN_EXIT
void    pars_clean_exit(t_data *data);
void    pars_clean_return(t_data *data);

//open_textures.c
int		open_textures_paths(t_data *data);
//--------------------------------------------LILIEN


//--------------------------------------------YVANN

//INIT_GRAPHICS
void	init_ray_values(t_ray *ray);
void	init_ray(t_ray *ray, t_data *data, int **int_map);
int		setup_mlx(t_ray *ray);
int		clean_close_windows(void *param);

//CLEAN_EXIT
void    pars_clean_exit(t_data *data);
void    pars_clean_return(t_data *data);

//RAYCASTING
int render_next_frame(t_ray *ray);

//RAY_UTILS
long get_current_time_millis(void);

//MAP_UTILS
int **allocate_int_map(t_data *data);
void set_player_position(t_ray *ray, int x, int y, char direction);
void parse_map(t_ray *ray, t_data *data, int **int_map);

//KEY_MOVE
int 	move_player(int keycode, t_ray *ray);
int 	rotate_player(int keycode, t_ray *ray);
int		key_hook(int keycode, t_ray *ray);

//--------------------------------------------YVANN

#endif
