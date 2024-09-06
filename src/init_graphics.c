#include "cub3d.h"

void init_ray(t_ray *ray)
{
    ray->screen_width = 640;
    ray->screen_height = 480;
    ray->screen_half_width = ray->screen_width / 2;
    ray->screen_half_height = ray->screen_height / 2;
    ray->render_delay = 30; // milliseconds
    ray->player_fov = 60.0; // degrees
    ray->player_half_fov = ray->player_fov / 2;
    ray->pos_x = 2.0;
    ray->pos_y = 2.0;
    ray->player_angle = 90.0;
    ray->ray_increment_angle = ray->player_fov / ray->screen_width;
    ray->raycasting_precision = 64;
    ray->dir_x = -1.0;
    ray->dir_y = 0;
    ray->plane_x = 0;
    ray->plane_y = 0.66;
    ray->time = 0;
    ray->old_time = 0;

    int example_map[10][10] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            ray->map[i][j] = example_map[i][j];
    }
}

int init_graphics(t_ray *ray)
{
    ray->mlx = mlx_init();
    if (!ray->mlx)
	{
		cleanup_graphics(ray);
		ft_printf("Error initializing mlx");
		return (1);
	}
    ray->mlx_win = mlx_new_window(ray->mlx, ray->screen_width, ray->screen_height, "Cub3D");
	if (!ray->mlx_win)
	{
		cleanup_graphics(ray);
		ft_printf("Error creating window");
		return (1);
	}
    ray->img = mlx_new_image(ray->mlx, ray->screen_width, ray->screen_height);
    if (!ray->img)
    {
        cleanup_graphics(ray);
        ft_printf("Error creating image");
        return (1);
    }
    //ray->addr = (int *)mlx_get_data_addr(ray->img, &ray->bpp, &ray->line_length, &ray->endian);
    return (0);
}
