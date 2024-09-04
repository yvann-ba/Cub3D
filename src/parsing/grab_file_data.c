/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_file_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:06:18 by lauger            #+#    #+#             */
/*   Updated: 2024/09/04 13:47:18 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_line(t_read_file *rf, char *id, int num_line)
{
	int	result;

	result = 0;
	if (rf == NULL || ft_strlen(id) < 3)
		return (-1);
	result = ft_strncmp(rf->tab_content[num_line], id, 3);
	
	return (result);
}

// static int	check_path(t_read_file *rf, int num_line)
// {
// 	char	*str;

// 	if (rf == NULL)
// 		clean_exit(rf->data);
// 	str = ft_substr(rf->tab_content[num_line], 3, ft_strlen(rf->tab_content[num_line]) - 3);
// 	if (str == NULL)
// 		return (-1);
// 	if (has_extenssion(str, ".xpm") == false)
// 	{
// 		free(str);
// 		return (-1);
// 	}
// 	if (num_line == 0)
// 		rf->p_north = str;
// 	else if (num_line == 1)
// 		rf->p_south = str;
// 	else if (num_line == 2)
// 		rf->p_west = str;
// 	else
// 		rf->p_east = str;
// 	printf("%s", str);
// 	return (0);
// }

static void	grab_sprite_paths(t_data *data)
{
	if (data->read_file == NULL)
		clean_exit(data);
	if (check_line(data->read_file, "NO ", 0) != 0
		|| check_line(data->read_file, "SO ", 1) != 0
		|| check_line(data->read_file, "WE ", 2) != 0
		|| check_line(data->read_file, "EA ", 3) != 0)
		{
			ft_printf(RED "Error:\nFile format is incorect\n" WHITE);
			clean_exit(data);
		}
		printf("**********RIGHT**********\n");
	// if	(check_path(data->read_file, 0) != 0
	// 	|| check_path(data->read_file, 1) != 0
	// 	|| check_path(data->read_file, 2) != 0
	// 	|| check_path(data->read_file, 3) != 0)
	// 	{
	// 		ft_printf(RED "Error:\nFile not have the extenssion .xpm\n" WHITE);
	// 		clean_exit(data);
	// 	}
		return ;
}

void	grab_data(t_data *data)
{
	if (!data || data == NULL)
		return ;
	grab_sprite_paths(data);
	return ;
}
