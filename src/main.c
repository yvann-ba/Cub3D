/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:46:38 by ybarbot           #+#    #+#             */
/*   Updated: 2024/09/24 12:46:39 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_data(t_data *data)
{
	data->f_int_rgb = ft_calloc(1, sizeof(t_rgb));
	data->c_int_rgb = ft_calloc(1, sizeof(t_rgb));
	if (data->f_int_rgb == NULL || data->c_int_rgb == NULL)
		return ;
	data->f_int_rgb->red = 0;
	data->f_int_rgb->green = 0;
	data->f_int_rgb->blue = 0;
	data->c_int_rgb->red = 0;
	data->c_int_rgb->green = 0;
	data->c_int_rgb->blue = 0;
	data->map = NULL;
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_ray	*ray;

	if (ac != 2)
	{
		ft_printf(RED"Error:\nNumber of arguments is incorrect:"
			WHITE" require format (./cub3d file.cub)\n");
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_printf("Error\nmalloc() failed\n", 2);
		exit(1);
	}
	init_data(data);
	data->fd_file = open_file(av[1], data);
	data->rf = read_file_to_string(data->fd_file, data);
	string_to_tab(data->rf);
	grab_data(data);
	ray = (t_ray *)malloc(sizeof(t_ray));
	ray->int_map = allocate_int_map(data);
	init_ray(ray, data, ray->int_map);
	setup_mlx(ray);
	return (0);
}
