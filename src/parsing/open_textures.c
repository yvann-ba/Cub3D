/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:49:32 by lauger            #+#    #+#             */
/*   Updated: 2024/09/16 09:26:34 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	all_clean_exit(t_data *data)
{
	if (data->north)
		free(data->north);
	if (data->south)
		free(data->south);
	if (data->west)
		free(data->west);
	if (data->east)
		free(data->east);
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

static void	put_str_exit(t_data *data, char *str)
{
	if (!data)
		return ;
	ft_putstr_fd(str, 2);
	all_clean_exit(data);
	return ;
}

static int	handle_opening(t_data *data)
{
	int	fd;

	fd = 0;
	fd = open(data->read_file->p_north, O_RDONLY);
	if (fd == -1)
		put_str_exit(data, RED "Error:\nImposible to open file\n" WHITE);
	close(fd);
	fd = open(data->read_file->p_south, O_RDONLY);
	if (fd == -1)
		put_str_exit(data, RED "Error:\nImposible to open file\n" WHITE);
	close(fd);
	fd = open(data->read_file->p_west, O_RDONLY);
	if (fd == -1)
		put_str_exit(data, RED "Error:\nImposible to open file\n" WHITE);
	close(fd);
	fd = open(data->read_file->p_east, O_RDONLY);
	if (fd == -1)
		put_str_exit(data, RED "Error:\nImposible to open file\n" WHITE);
	close(fd);
	return (fd);
}

int	open_textures_paths(t_data *data)
{
	if (!data)
		return (-1);
	handle_opening(data);
	data->size_image = 512;
	data->north = mlx_xpm_file_to_image(data->ray->mlx, data->read_file->p_north, &data->size_image, &data->size_image);
	data->south = mlx_xpm_file_to_image(data->ray->mlx, data->read_file->p_south, &data->size_image, &data->size_image);
	data->west = mlx_xpm_file_to_image(data->ray->mlx, data->read_file->p_west, &data->size_image, &data->size_image);
	data->east = mlx_xpm_file_to_image(data->ray->mlx, data->read_file->p_east, &data->size_image, &data->size_image);
	if (data->north == NULL || data->south == NULL || data->west || data->east)
	{
		if (data->north)
			free(data->north);
		if (data->south)
			free(data->south);
		if (data->west)
			free(data->west);
		if (data->east)
			free(data->east);
	}
	return (0);
}