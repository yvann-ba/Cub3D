#ifndef CUB3D_H
# define CUB3D_H

# define BUFFER_SIZE 1024

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

	int     screen_width;
	int     screen_height;
	int		screen_half_width;
	int		screen_half_height;
	int		render_delay;
	double	player_fov;
	double	player_half_fov;
	double	player_x;
	double	player_y;
	double	player_angle;
	double	ray_increment_angle;
	int		raycasting_precision;
	int		map[10][10];
} t_ray;


//INIT
void	init_ray(t_ray *ray);
//int		init_graphics(t_graphics *graph);

//FILE
int         open_file(char *file, t_data *data);
t_read_file *read_file_to_string(int fd, t_data *data);
void        string_to_tab(t_read_file *rf);

//EXITS
void    clean_exit(t_data *data);
void    clean_return(t_data *data);
void	cleanup_graphics(t_ray *ray);


typedef struct	s_ray
{
	double		posx; //position x du joueur
	double		posy; //position y du joueur
	double		dirx; //vecteur de direction (commence à -1 pour N, 1 pour S, 0 sinon)
	double		diry; //vecteur de direction (commence à -1 pour W, 1 pour E, 0 sinon)
	double		planx; //vecteur du plan (commence à 0.66 pour E, -0.66 pour W, 0 sinon)
	double		plany; //vecteur du plan (commence à 0.66 pour N, -0.66 pour S, 0 sinon)
	double		raydirx; //calcul de direction x du rayon
	double		raydiry; //calcul de direction y du rayon
	double		camerax; //point x sur la plan camera : Gauche ecran = -1, milieu = 0, droite = 1
	int		mapx; // coordonée x du carré dans lequel est pos
	int		mapy; // coordonnée y du carré dans lequel est pos
	double		sidedistx; //distance que le rayon parcours jusqu'au premier point d'intersection vertical (=un coté x)
	double		sidedisty; //distance que le rayon parcours jusqu'au premier point d'intersection horizontal (= un coté y)
	double		deltadistx; //distance que rayon parcours entre chaque point d'intersection vertical
	double		deltadisty; //distance que le rayon parcours entre chaque point d'intersection horizontal
	int		stepx; // -1 si doit sauter un carre dans direction x negative, 1 dans la direction x positive
	int		stepy; // -1 si doit sauter un carre dans la direction y negative, 1 dans la direction y positive
	int		hit; // 1 si un mur a ete touche, 0 sinon
	int		side; // 0 si c'est un cote x qui est touche (vertical), 1 si un cote y (horizontal)
	double		perpwalldist; // distance du joueur au mur
	int		lineheight; //hauteur de la ligne a dessiner
	int		drawstart; //position de debut ou il faut dessiner
	int		drawend; //position de fin ou il faut dessiner
	int		x; //permet de parcourir tous les rayons
}	

#endif