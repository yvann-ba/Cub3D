/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_file_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:06:18 by lauger            #+#    #+#             */
/*   Updated: 2024/09/20 09:28:46 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_line(t_read_file *rf, char *id, int num_line, int value_check)
{
	int		result;

	result = 0;
	if (rf == NULL || ft_strlen(id) < (size_t)value_check)
		return (-2);
	result = ft_strncmp(rf->tab_content[num_line], id, value_check);
	return (result);
}

static int	check_path(t_read_file *rf, int num_line, char *id)
{
	char	*str;

	if (rf == NULL)
		pars_clean_exit(rf->data);
	str = ft_substr(rf->tab_content[num_line], 3, ft_strlen(rf->tab_content[num_line]) - 3);
	if (str == NULL)
		return (-1);
	if (has_extenssion(str, ".xpm") == false)
	{
		free(str);
		return (-1);
	}
	if (ft_strcmp(id, "NO") == 0)
	{
		if (rf->p_north != NULL)
			return (-1);
		rf->p_north = str;
	}
	else if (ft_strcmp(id, "SO") == 0)
	{
		if (rf->p_south != NULL)
			return (-1);
		rf->p_south = str;
	}
	else if (ft_strcmp(id, "WE") == 0)
	{
	if (rf->p_west != NULL)
			return (-1);
		rf->p_west = str;
	}
	else if (ft_strcmp(id, "EA") == 0)
	{
		if (rf->p_east != NULL)
			return (-1);
		rf->p_east = str;
	}
	return (0);
}

static int	valid_value(t_data *data, char *id, int i)
{
	if (ft_strstr(data->read_file->tab_content[i], id))
	{
		if (check_line(data->read_file, id, i, 2) != 0)
		{
			ft_printf(RED "EEError:\nFile format is incorect\n" WHITE);
			pars_clean_exit(data);
		}
		if (check_path(data->read_file, i, id) != 0)
		{
			ft_printf(RED "Error:\nFile not have the extenssion .xpm\n" WHITE);
			pars_clean_exit(data);
		}
	}
	return (0);
}

static void	grab_sprite_paths(t_data *data)
{
	int	i;

	i = 0;
	if (data->read_file == NULL)
		pars_clean_exit(data);
	while(data->read_file->tab_content[i])
	{
		valid_value(data, "NO", i);
		valid_value(data, "SO", i);
		valid_value(data, "WE", i);
		valid_value(data, "EA", i);
		i++;
	}
		return ;
}

static void	manage_utilization_flood_fill(t_data *data, char **c_map)
{
	int	i;
	int	j;

	i = 0;
	while(c_map[i] != NULL)
	{
		j = 0;
		while (c_map[i][j] != '\0')
		{
			if (flood_fill(c_map, i, j) == -1)
			{
				ft_putstr_fd(RED"Error:\nInvalid Map:" WHITE" must be around of walls\n", 2);
				ft_free_tab(c_map);
				pars_clean_exit(data);
			}
			j++;
		}
		i++;
	}
}

void	grab_data(t_data *data)
{
	char	**c_map;

	if (!data || data == NULL)
		return ;
	grab_sprite_paths(data);
	grab_color(data);
	grab_map(data);
	replace_space_to_wall(data);
	c_map = ft_copy_tab(data->map, ft_tab_len(data->map));
	if (c_map == NULL)
		return ;
	manage_utilization_flood_fill(data, c_map);
	open_textures_paths(data, c_map);
	ft_free_tab(c_map);
	return ;
}
