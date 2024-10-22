/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:47:43 by ybarbot           #+#    #+#             */
/*   Updated: 2024/10/22 13:39:46 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_pos_ns(t_ray *ray, char direction)
{
	if (direction == 'N')
	{
		ray->dir_x = -1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = 0.66;
	}
	else if (direction == 'S')
	{
		ray->dir_x = 1;
		ray->dir_y = 0;
		ray->plane_x = 0;
		ray->plane_y = -0.66;
	}
}

static void	set_player_pos_ew(t_ray *ray, char direction)
{
	if (direction == 'E')
	{
		ray->dir_x = 0;
		ray->dir_y = 1;
		ray->plane_x = 0.66;
		ray->plane_y = 0;
	}
	else if (direction == 'W')
	{
		ray->dir_x = 0;
		ray->dir_y = -1 ;
		ray->plane_x = -0.66;
		ray->plane_y = 0;
	}
}

void	set_player_position(t_ray *ray, int x, int y, char direction)
{
	ray->pos_x = y + 0.5;
	ray->pos_y = x + 0.5;
	set_player_pos_ns(ray, direction);
	set_player_pos_ew(ray, direction);
}

void	move_player(int keycode, t_ray *ray)
{
	move_player_y(keycode, ray);
	move_player_x(keycode, ray);
}
