/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_file_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:06:18 by lauger            #+#    #+#             */
/*   Updated: 2024/10/15 09:10:19 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_line(t_read_file *rf, char *id, int num_line, int value_check)
{
	int		result;
	char	*line;

	result = 0;
	line = NULL;
	line = deblank(rf->tab_content[num_line], 0);
	if (rf == NULL || ft_strlen(id) < (size_t)value_check || !line)
		return (-2);
	result = ft_strncmp(line, id, value_check);
	free(line);
	return (result);
}

static int	valid_value(t_data *data, char *id, int i, int *nb_paths)
{
	if (ft_strstr(data->rf->tab_content[i], id))
	{
		*nb_paths += 1;
		if (*nb_paths > 4)
		{
			ft_printf(RED "Error:\nThe File must have 4 paths "
				"(NO, SO, WE, EA)\n" WHITE);
			pars_clean_exit(data);
		}
		if (check_line(data->rf, id, i, 2) != 0)
		{
			ft_printf(RED "Error:\nFile format is incorrect\n" WHITE);
			pars_clean_exit(data);
		}
		if (check_path(data->rf, i, id) != 0)
		{
			ft_printf(RED "Error:\nFile not have the extension .xpm\n" WHITE);
			pars_clean_exit(data);
		}
	}
	return (0);
}

static void	grab_sprite_paths(t_data *data)
{
	int	i;
	int	nb_paths;

	i = 0;
	nb_paths = 0;
	if (data->rf == NULL)
		pars_clean_exit(data);
	while (data->rf->tab_content[i])
	{
		valid_value(data, "NO", i, &nb_paths);
		valid_value(data, "SO", i, &nb_paths);
		valid_value(data, "WE", i, &nb_paths);
		valid_value(data, "EA", i, &nb_paths);
		i++;
	}
	if (nb_paths != 4)
	{
		ft_printf(RED "Error:\nThe File must have 4 paths "
			"(NO, SO, WE, EA)\n" WHITE);
		pars_clean_exit(data);
	}
	return ;
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
