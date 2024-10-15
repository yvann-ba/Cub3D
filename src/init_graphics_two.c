/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:13:34 by lauger            #+#    #+#             */
/*   Updated: 2024/09/25 10:20:03 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	free_img_mlx_error(t_ray *ray, t_data *data)
{
	printf(RED"Error:\nimage paths is incorrect\n"WHITE);
	if (ray->tx_north->img)
		mlx_destroy_image(ray->mlx, ray->tx_north->img);
	if (ray->tx_south->img)
		mlx_destroy_image(ray->mlx, ray->tx_south->img);
	if (ray->tx_west->img)
		mlx_destroy_image(ray->mlx, ray->tx_west->img);
	if (ray->tx_east->img)
		mlx_destroy_image(ray->mlx, ray->tx_east->img);
	if (data->ray->mlx)
		mlx_destroy_display(data->ray->mlx);
	if (ray->tx)
		free(ray->tx);
	if (ray->tx_north)
		free(ray->tx_north);
	if (ray->tx_south)
		free(ray->tx_south);
	if (ray->tx_west)
		free(ray->tx_west);
	if (ray->tx_east)
		free(ray->tx_east);
	free(data->ray->mlx);
	ft_free_tab_int(data->ray->int_map, data->map_height);
	free(data->ray);
	pars_clean_exit(data);
}

void	paths_to_mlx_image_second_part(t_ray *r, t_data *data)
{
	r->tx_north->img = mlx_xpm_file_to_image(data->ray->mlx,
			data->rf->p_north, &r->tx_north->width, &r->tx_north->height);
	r->tx_south->img = mlx_xpm_file_to_image(data->ray->mlx,
			data->rf->p_south, &r->tx_south->width, &r->tx_south->height);
	r->tx_west->img = mlx_xpm_file_to_image(data->ray->mlx,
			data->rf->p_west, &r->tx_west->width, &r->tx_west->height);
	r->tx_east->img = mlx_xpm_file_to_image(data->ray->mlx,
			data->rf->p_east, &r->tx_east->width, &r->tx_east->height);
	if (r->tx_north->img == NULL || r->tx_south->img == NULL
		|| r->tx_west->img == NULL || r->tx_east->img == NULL)
		free_img_mlx_error(r, data);
	r->tx_north->addr = mlx_get_data_addr(r->tx_north->img, &r->tx_north->bpp,
			&r->tx_north->size_line, &r->tx_north->endian);
	r->tx_south->addr = mlx_get_data_addr(r->tx_south->img,
			&r->tx_south->bpp, &r->tx_south->size_line, &r->tx_south->endian);
	r->tx_west->addr = mlx_get_data_addr(r->tx_west->img,
			&r->tx_west->bpp, &r->tx_west->size_line, &r->tx_west->endian);
	r->tx_east->addr = mlx_get_data_addr(r->tx_east->img,
			&r->tx_east->bpp, &r->tx_east->size_line, &r->tx_east->endian);
}
