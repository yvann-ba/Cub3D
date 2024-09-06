/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_file_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:06:18 by lauger            #+#    #+#             */
/*   Updated: 2024/09/06 09:32:20 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_line(t_read_file *rf, char *id, int num_line, int value_check)
{
	int	result;

	result = 0;
	if (rf == NULL || ft_strlen(id) < (size_t)value_check)
		return (-1);
	result = ft_strncmp(rf->tab_content[num_line], id, value_check);
	
	return (result);
}

static int	check_path(t_read_file *rf, int num_line)
{
	char	*str;

	if (rf == NULL)
		clean_exit(rf->data);
	str = ft_substr(rf->tab_content[num_line], 3, ft_strlen(rf->tab_content[num_line]) - 3);
	if (str == NULL)
		return (-1);
	if (has_extenssion(str, ".xpm") == false)
	{
		free(str);
		return (-1);
	}
	if (num_line == 0)
		rf->p_north = str;
	else if (num_line == 1)
		rf->p_south = str;
	else if (num_line == 2)
		rf->p_west = str;
	else
		rf->p_east = str;
	return (0);
}

static void	grab_sprite_paths(t_data *data)
{
	if (data->read_file == NULL)
		clean_exit(data);
	if (check_line(data->read_file, "NO ", 0, 3) != 0
		|| check_line(data->read_file, "SO ", 1, 3) != 0
		|| check_line(data->read_file, "WE ", 2, 3) != 0
		|| check_line(data->read_file, "EA ", 3, 3) != 0)
		{
			ft_printf(RED "Error:\nFile format is incorect\n" WHITE);
			clean_exit(data);
		}
	if	(check_path(data->read_file, 0) != 0
		|| check_path(data->read_file, 1) != 0
		|| check_path(data->read_file, 2) != 0
		|| check_path(data->read_file, 3) != 0)
		{
			ft_printf(RED "Error:\nFile not have the extenssion .xpm\n" WHITE);
			clean_exit(data);
		}
		return ;
}

// static void	open_xpm_file(t_data *data)
// {
// 	data->north = mlx_xpm_file_to_image(mlx, data->read_file->p_north, &img_width, &img_height);
// 	data->south = mlx_xpm_file_to_image(mlx, data->read_file->p_south, &img_width, &img_height);
// 	data->west = mlx_xpm_file_to_image(mlx, data->read_file->p_west, &img_width, &img_height);
// 	data->east = mlx_xpm_file_to_image(mlx, data->read_file->p_east, &img_width, &img_height);
// 	if (data->north == NULL || data->south == NULL || data->west == NULL || data->east == NULL)
// 	{
// 		ft_printf(RED, "Error:\nImposible to open file.xpm"WHITE);
// 		clean_exit(data);
// 	}
// 	return ;
// }

void	grab_data(t_data *data)
{
	if (!data || data == NULL)
		return ;
	//printf("-----%p------", data->read_file);
	grab_sprite_paths(data);
	//open_xpm_file(data);
	//printf("here-------");
	grab_color(data);
	grab_map(data);
	return ;
}
