/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:07:02 by ybarbot           #+#    #+#             */
/*   Updated: 2024/09/24 12:49:28 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_2(int keycode, t_ray *ray, double \
*old_dir_x, double *old_plane_x)
{
	if (keycode == 65361)
	{
		*old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(ray->rot_speed) \
		- ray->dir_y * sin(ray->rot_speed);
		ray->dir_y = *old_dir_x * sin(ray->rot_speed) \
		+ ray->dir_y * cos(ray->rot_speed);
		*old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(ray->rot_speed) \
		- ray->plane_y * sin(ray->rot_speed);
		ray->plane_y = *old_plane_x * sin(ray->rot_speed) \
		+ ray->plane_y * cos(ray->rot_speed);
	}
}

void	rotate_1(int keycode, t_ray *ray)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == 65363)
	{
		old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(-ray->rot_speed) \
		- ray->dir_y * sin(-ray->rot_speed);
		ray->dir_y = old_dir_x * sin(-ray->rot_speed) \
		+ ray->dir_y * cos(-ray->rot_speed);
		old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(-ray->rot_speed) \
		- ray->plane_y * sin(-ray->rot_speed);
		ray->plane_y = old_plane_x * sin(-ray->rot_speed) \
		+ ray->plane_y * cos(-ray->rot_speed);
	}
	rotate_2(keycode, ray, &old_dir_x, &old_plane_x);
}

void	move_player_y(int keycode, t_ray *ray)
{
	if (keycode == 119)
	{
		if (ray->int_map[(int)(ray->pos_x + ray->dir_x
				* ray->move_speed)][(int)(ray->pos_y)] == 0)
			ray->pos_x += ray->dir_x * ray->move_speed;
		if (ray->int_map[(int)(ray->pos_x)][(int)(ray->pos_y + ray->dir_y
				* ray->move_speed)] == 0)
			ray->pos_y += ray->dir_y * ray->move_speed;
	}
	if (keycode == 115)
	{
		if (ray->int_map[(int)(ray->pos_x - ray->dir_x
				* ray->move_speed)][(int)(ray->pos_y)] == 0)
			ray->pos_x -= ray->dir_x * ray->move_speed;
		if (ray->int_map[(int)(ray->pos_x)][(int)(ray->pos_y
				- ray->dir_y * ray->move_speed)] == 0)
			ray->pos_y -= ray->dir_y * ray->move_speed;
	}
}

void	move_player_x(int keycode, t_ray *ray)
{
	if (keycode == 100)
	{
		if (ray->int_map[(int)(ray->pos_x
				- ray->dir_x * ray->move_speed)][(int)(ray->pos_y)] == 0)
			ray->pos_y -= ray->dir_x * ray->move_speed;
		if (ray->int_map[(int)(ray->pos_x)][(int)(ray->pos_y
				- ray->dir_y * ray->move_speed)] == 0)
			ray->pos_x += ray->dir_y * ray->move_speed;
	}
	if (keycode == 97)
	{
		if (ray->int_map[(int)(ray->pos_x + ray->dir_x
				* ray->move_speed)][(int)(ray->pos_y)] == 0)
			ray->pos_y += ray->dir_x * ray->move_speed;
		if (ray->int_map[(int)(ray->pos_x)][(int)(ray->pos_y
				+ ray->dir_y * ray->move_speed)] == 0)
			ray->pos_x -= ray->dir_y * ray->move_speed;
	}
}

int	key_hook(int keycode, t_ray *ray)
{
	move_player(keycode, ray);
	rotate_1(keycode, ray);
	if (keycode == 65307)
		clean_close_windows(ray->data);
	return (0);
}
