/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:46:09 by ybarbot           #+#    #+#             */
/*   Updated: 2024/09/24 12:46:27 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long	get_current_time_millis(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	fill_floor_cell(t_ray *ray, int *i, int *x)
{
	while ((*i) < SCREEN_HEIGHT)
	{
		ray->addr_c[*i * ray->size_line / 4 + *x] = ray->data->f_hex_rgb;
		(*i)++;
	}
	*i = ray->draw_start;
	while (*i >= 0)
	{
		ray->addr_c[*i * ray->size_line / 4 + *x] = ray->data->c_hex_rgb;
		(*i)--;
	}
}
