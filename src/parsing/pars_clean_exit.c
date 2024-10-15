/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_clean_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:12:27 by lauger            #+#    #+#             */
/*   Updated: 2024/09/24 12:48:37 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	all_clean_exit(t_data *data)
{
	if (data->ray->img)
		mlx_destroy_image(data->ray->mlx, data->ray->img);
	if (data->ray->mlx)
		mlx_destroy_window(data->ray->mlx, data->ray->mlx_win);
	if (data->ray->mlx)
		mlx_destroy_display(data->ray->mlx);
	free(data->ray->mlx);
	ft_free_tab_int(data->ray->int_map, data->map_height);
	free(data->ray);
	pars_clean_exit(data);
}

void	pars_clean_exit(t_data *data)
{
	if (data->rf->p_north)
		free(data->rf->p_north);
	if (data->rf->p_south)
		free(data->rf->p_south);
	if (data->rf->p_west)
		free(data->rf->p_west);
	if (data->rf->p_east)
		free(data->rf->p_east);
	if (data->rf->str_content)
		free(data->rf->str_content);
	if (data->rf->tab_content)
		ft_free_tab(data->rf->tab_content);
	close (data->fd_file);
	if (data->rf)
		free(data->rf);
	if (data->c_int_rgb)
		free(data->c_int_rgb);
	if (data->f_int_rgb)
		free(data->f_int_rgb);
	if (data->map)
		ft_free_tab(data->map);
	if (data)
		free(data);
	exit(0);
}

void	pars_clean_return(t_data *data)
{
	if (data->rf->str_content)
		free(data->rf->str_content);
	if (data->rf->tab_content)
		ft_free_tab(data->rf->tab_content);
	if (data->rf->p_north)
		free(data->rf->p_north);
	if (data->rf->p_south)
		free(data->rf->p_south);
	if (data->rf->p_west)
		free(data->rf->p_west);
	if (data->rf->p_east)
		free(data->rf->p_east);
	if (data->rf)
		free(data->rf);
	if (data->c_int_rgb)
		free(data->c_int_rgb);
	if (data->f_int_rgb)
		free(data->f_int_rgb);
	if (data->map)
		ft_free_tab(data->map);
	if (data)
		free(data);
	return ;
}
