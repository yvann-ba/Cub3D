/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:46:09 by ybarbot           #+#    #+#             */
/*   Updated: 2024/10/15 14:35:19 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long	get_current_time_millis(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void fill_floor_cell(t_ray *ray, int *i, int *x)
{
    int *addr_int = (int *)(ray->addr);
    int size_line_int = ray->size_line / 4;

    while ((*i) < SCREEN_HEIGHT)
    {
        addr_int[(*i) * size_line_int + *x] = ray->data->f_hex_rgb;
        (*i)++;
    }
    *i = ray->draw_start;
    while (*i >= 0)
    {
        addr_int[(*i) * size_line_int + *x] = ray->data->c_hex_rgb;
        (*i)--;
    }
}

