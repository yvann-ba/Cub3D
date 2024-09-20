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

void	paths_to_mlx_image(t_data *data)
{
	if (!data)
		return ;
	data->north = mlx_xpm_file_to_image(data->ray->mlx, data->read_file->p_north, (int *)TEX_WIDTH, (int *)TEX_HEIGHT);
	data->south = mlx_xpm_file_to_image(data->ray->mlx, data->read_file->p_south, (int *)TEX_WIDTH, (int *)TEX_HEIGHT);
	data->west = mlx_xpm_file_to_image(data->ray->mlx, data->read_file->p_west, (int *)TEX_WIDTH, (int *)TEX_HEIGHT);
	data->east = mlx_xpm_file_to_image(data->ray->mlx, data->read_file->p_east, (int *)TEX_WIDTH, (int *)TEX_HEIGHT);
	if (data->north == NULL || data->south == NULL || data->west || data->east)
	{
		printf(RED"Error:\nimage paths is incorrect\n"WHITE);
		mlx_destroy_image(data->ray->mlx, data->north);
		mlx_destroy_image(data->ray->mlx, data->south);
		mlx_destroy_image(data->ray->mlx, data->west);
		mlx_destroy_image(data->ray->mlx, data->east);
		if (data->ray->mlx)
			mlx_destroy_display(data->ray->mlx);
		free(data->ray->mlx);
		ft_free_tab_int(data->ray->int_map, data->map_height);
		free(data->ray);
		pars_clean_exit(data);
		exit(0);
	}
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
	//free_mlx_images(data);
	if (data->ray->img)
		mlx_destroy_image(data->ray->mlx, data->ray->img);
	if (data->ray->mlx)
		mlx_destroy_window(data->ray->mlx, data->ray->mlx_win);
	if (data->ray->mlx)
		mlx_destroy_display(data->ray->mlx);
	ft_free_tab_int(data->ray->int_map, data->map_height);
	free(data->ray->mlx);
	free(data->ray);
	pars_clean_exit(data);
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
	//paths_to_mlx_image(ray->data);
	ray->mlx_win = mlx_new_window(ray->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!ray->mlx_win)
	{
		free(ray->mlx_win);
		printf("Error:mlx_new_window() failed\n");
		return(1);
	}
	ray->img = mlx_new_image(ray->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	ray->addr = (int *)mlx_get_data_addr(ray->img, &ray->bpp, &ray->line_length, &ray->endian);

	mlx_hook(ray->mlx_win, 2, 1L << 0, key_hook, ray);
	mlx_loop_hook(ray->mlx, render_next_frame, ray);
	mlx_hook(ray->mlx_win, 17, 0, clean_close_windows, ray->data);
	mlx_loop(ray->mlx);
	return (0);
}
