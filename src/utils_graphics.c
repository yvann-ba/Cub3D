#include "cub3d.h"


void	cleanup_graphics(t_ray *ray)
{
	if (ray->img)
		mlx_destroy_image(ray->mlx, ray->img);
	if (ray->mlx_win)
		mlx_destroy_window(ray->mlx, ray->mlx_win);
	if (ray->mlx)
		mlx_destroy_display(ray->mlx);
	free(ray->mlx);
	//free_map(ray->map, ray->height);
}