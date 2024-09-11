#include "cub3d.h"

static void	init_data(t_data *data)
{
	data->f_rgb = ft_calloc(1, sizeof(t_rgb));
	data->c_rgb = ft_calloc(1, sizeof(t_rgb));
	if (data->f_rgb == NULL || data->c_rgb == NULL)
		return ;
	data->f_rgb->red = 0;
	data->f_rgb->green = 0;
	data->f_rgb->blue = 0;
	data->c_rgb->red = 0;
	data->c_rgb->green = 0;
	data->c_rgb->blue = 0;
	data->map = NULL;
}

int main(int ac, char **av)
{
	t_data *data;
	t_ray *ray;

	if (ac != 2)
	{
		ft_printf(RED"Error:\nNumber of arguments is incorrect:" WHITE" require format (./cub3d file.cub)\n");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_printf("Error\nmalloc() failed\n", 2);
		exit(1);
	}
	init_data(data);
	data->fd_map = open_file(av[1], data);
	data->read_file = read_file_to_string(data->fd_map, data);
	string_to_tab(data->read_file);
	grab_data(data);
	ray = (t_ray *)malloc(sizeof(t_ray));
	ray->int_map = allocate_int_map(data);
	init_ray(ray, data, ray->int_map);
	setup_mlx(ray);
	return (0);
}
