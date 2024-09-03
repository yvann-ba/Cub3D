#ifndef CUB3D_H
# define CUB3D_H

# define WIN_HEIGHT 600
# define WIN_WIDTH 800
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

typedef struct s_data
{
    int  fd_map;
    void *mlx;
    void *mlx_win;
    void *img;
    int *addr;
    int bpp;
    int line_length;
    int endian;
} t_data;

//FILE
int    open_file(char *file, t_data *data);

//EXITS
void    clean_exit(t_data *data);

#endif