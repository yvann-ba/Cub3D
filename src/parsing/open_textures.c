/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:49:32 by lauger            #+#    #+#             */
/*   Updated: 2024/09/16 11:26:45 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	put_str_exit(t_data *data, char *str, char **c_map)
{
	if (!data)
		return ;
	ft_putstr_fd(str, 2);
	ft_free_tab(c_map);
	pars_clean_exit(data);
	return ;
}

static int	handle_opening(t_data *data, char **c_map)
{
	int	fd;

	fd = 0;
	fd = open(data->read_file->p_north, O_RDONLY);
	if (fd == -1)
		put_str_exit(data, RED "Error:\nImposible to open file\n" WHITE, c_map);
	close(fd);
	fd = open(data->read_file->p_south, O_RDONLY);
	if (fd == -1)
		put_str_exit(data, RED "Error:\nImposible to open file\n" WHITE, c_map);
	close(fd);
	fd = open(data->read_file->p_west, O_RDONLY);
	if (fd == -1)
		put_str_exit(data, RED "Error:\nImposible to open file\n" WHITE, c_map);
	close(fd);
	fd = open(data->read_file->p_east, O_RDONLY);
	if (fd == -1)
		put_str_exit(data, RED "Error:\nImposible to open file\n" WHITE, c_map);
	close(fd);
	return (fd);
}

int	open_textures_paths(t_data *data, char **c_map)
{
	if (!data)
		return (-1);
	handle_opening(data, c_map);
	return (0);
}