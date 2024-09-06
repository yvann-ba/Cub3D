#ifndef CUB3D_H
# define CUB3D_H

# define WIN_HEIGHT 600
# define WIN_WIDTH 800
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
# include "../Libft/libft.h"

typedef struct s_data t_data;
typedef struct s_read_file t_read_file;

typedef struct s_read_file
{
    t_data  *data;
    char    **tab_content;
    char    buffer[BUFFER_SIZE];
    char    *str_content;
    ssize_t bytes_read;
    size_t  total_size;
    size_t  new_size;
    char        *p_north;
    char        *p_south;
    char        *p_west;
    char        *p_east;
} t_read_file;

typedef struct s_rgb
{
    unsigned int  red;
    unsigned int  green;
    unsigned int  blue;
} t_rgb;

typedef struct s_data
{
    void        *north;
    void        *south;
    void        *west;
    void        *east;
    t_rgb       *f_rgb;
    t_rgb       *c_rgb;
    int         fd_map;
    char        **map;
    t_read_file *read_file;
} t_data;


//FILE
int         open_file(char *file, t_data *data);
t_read_file *read_file_to_string(int fd, t_data *data);
void        string_to_tab(t_read_file *rf);
void	    grab_data(t_data *data);
bool        has_extenssion(char *filename, char *extenssion);
int	        check_line(t_read_file *rf, char *id, int num_line, int value_check);
void        grab_color(t_data *data);
void        grab_map(t_data *data);

//TEMPOARY FUNCTIONS
void    print_2d_array(char **array, int rows);

//EXITS
void    clean_exit(t_data *data);
void    clean_return(t_data *data);

#endif