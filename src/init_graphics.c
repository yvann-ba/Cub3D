#include "cub3d.h"

void init_ray_values(t_ray *ray)
{
	ray->screen_width = 640;
	ray->screen_height = 480;
	ray->screen_half_width = ray->screen_width / 2;
	ray->screen_half_height = ray->screen_height / 2;
	ray->render_delay = 30; // milliseconds
	ray->player_fov = 60.0; // degrees
	ray->player_half_fov = ray->player_fov / 2;
	ray->player_angle = 90.0;
	ray->ray_increment_angle = ray->player_fov / ray->screen_width;
	ray->raycasting_precision = 64;
	ray->time = 0;
	ray->old_time = 0;
	ray->hit = 0;
}

void    init_ray(t_ray *ray, t_data *data, int **int_map)
{
	if (!ray)
	{
		ft_printf("Error\nmalloc() failed\n", 2);
		exit(1);
	}
	init_ray_values(ray);
	parse_map(ray, data, int_map);
	ray->int_map = int_map;
	data->ray = ray;
	ray->data = data;
}

int	clean_close_windows(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_printf(RED"~~~~~~~~~~~~%p~~~~~~~~~~~\n"WHITE, data->ray->mlx);
	if (data->ray->img)
		mlx_destroy_image(data->ray->mlx, data->ray->img);
	if (data->ray->mlx)
		mlx_destroy_window(data->ray->mlx, data->ray->mlx_win);
	if (data->ray->mlx)
		mlx_destroy_display(data->ray->mlx);
	free(data->ray->mlx);
	free(data->ray);
	pars_clean_exit(data);
	//exit(0);
	return (0);
}

int setup_mlx(t_ray *ray)
{
	ray->mlx = mlx_init();
	if (ray->mlx == NULL)
	{
		printf("Error:mlx_init() failed\n");
		return (1);
	}
	ray->mlx_win = mlx_new_window(ray->mlx, ray->screen_width, ray->screen_height, "Cub3D");
	if (!ray->mlx_win)
	{
		free(ray->mlx_win);
		printf("Error:mlx_new_window() failed\n");
		return(1);
	}
	ray->img = mlx_new_image(ray->mlx, ray->screen_width, ray->screen_height);
	ray->addr = (int *)mlx_get_data_addr(ray->img, &ray->bpp, &ray->line_length, &ray->endian);

	mlx_hook(ray->mlx_win, 2, 1L << 0, key_hook, ray);
	mlx_loop_hook(ray->mlx, render_next_frame, ray);
	mlx_hook(ray->mlx_win, 17, 0, clean_close_windows, ray->data);
	mlx_loop(ray->mlx);
	return (0);
}
