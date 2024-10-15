/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:52:58 by lauger            #+#    #+#             */
/*   Updated: 2024/10/15 15:02:29 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	paths_to_mlx_image(t_ray *r, t_data *data)
{
	r->tx = NULL;
	r->tx_north = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	r->tx_south = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	r->tx_west = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	r->tx_east = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	if (!r->tx_north || !r->tx_south || !r->tx_east || !r->tx_west)
		free_img_mlx_error(r, data);
	if (!r->data->rf->p_north || !r->data->rf->p_south
		|| !r->data->rf->p_west || !r->data->rf->p_east)
		free_img_mlx_error(r, data);
	paths_to_mlx_image_second_part(r, data);
}

void	init_ray(t_ray *ray, t_data *data, int **int_map)
{
	if (!ray)
	{
		ft_printf("Error\nmalloc() failed\n", 2);
		exit(1);
	}
	ray->time = 0;
	ray->old_time = 0;
	parse_map(ray, data, int_map);
	ray->int_map = int_map;
	data->ray = ray;
	ray->data = data;
}

int	clean_close_windows(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_destroy_image(data->ray->mlx, data->ray->tx_north->img);
	mlx_destroy_image(data->ray->mlx, data->ray->tx_south->img);
	mlx_destroy_image(data->ray->mlx, data->ray->tx_west->img);
	mlx_destroy_image(data->ray->mlx, data->ray->tx_east->img);
	free(data->ray->tx_north);
	free(data->ray->tx_south);
	free(data->ray->tx_west);
	free(data->ray->tx_east);
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

int	setup_mlx(t_ray *ray)
{
	ray->mlx = mlx_init();
	if (!ray->mlx || !ray->data)
		return (1);
	paths_to_mlx_image(ray, ray->data);
	ray->mlx_win = mlx_new_window(ray->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!ray->mlx_win)
	{
		free(ray->mlx_win);
		printf("Error:mlx_new_window() failed\n");
		return (1);
	}
	ray->img = mlx_new_image(ray->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	ray->addr = mlx_get_data_addr(ray->img, &ray->bpp,
			&ray->size_line, &ray->endian);
	mlx_hook(ray->mlx_win, 2, 1L << 0, key_hook, ray);
	mlx_loop_hook(ray->mlx, render_next_frame, ray);
	mlx_hook(ray->mlx_win, 17, 0, clean_close_windows, ray->data);
	mlx_loop(ray->mlx);
	return (0);
}
