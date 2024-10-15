/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:10:36 by ybarbot           #+#    #+#             */
/*   Updated: 2024/09/24 14:19:24 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_algo(t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->int_map[ray->map_x][ray->map_y] > 0)
			ray->hit = 1;
	}
}

void	draw_texture(t_ray *ray, int *x)
{
	int	y;
	int	color;
	int	tex_y;
	int	d;

	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		d = y * 256 - SCREEN_HEIGHT * 128 + ray->line_height * 128;
		tex_y = ((d * ray->tx->height) / ray->line_height) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= ray->tx->height)
			tex_y = ray->tx->height - 1;
		color = *(int *)(ray->tx->addr + (tex_y * ray->tx->size_line \
		+ ray->tex_x * (ray->tx->bpp / 8)));
		*(int *)(ray->addr + (y * ray->size_line
					+ (*x) * (ray->bpp / 8))) = color;
		y++;
	}
}

void	assign_dir_tx(t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->tx = ray->tx_south;
	else if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tx = ray->tx_north;
	else if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->tx = ray->tx_west;
	else
		ray->tx = ray->tx_east;
}

void	assign_calculate_ray(t_ray *ray, int *i)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
	*i = ray->draw_end;
}

int	render_next_frame(t_ray *ray)
{
	int	x;
	int	i;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		calculate_ray(ray, &x);
		dda_algo(ray);
		assign_calculate_ray(ray, &i);
		fill_floor_cell(ray, &i, &x);
		assign_dir_tx(ray);
		texture_calculations(ray);
		draw_texture(ray, &x);
		x++;
	}
	ray->old_time = ray->time;
	ray->time = get_current_time_millis();
	ray->frame_time = (ray->time - ray->old_time) / 1000.0;
	mlx_put_image_to_window(ray->mlx, ray->mlx_win, ray->img, 0, 0);
	ray->move_speed = ray->frame_time * 10.0;
	ray->rot_speed = ray->frame_time * 3.0;
	return (0);
}
