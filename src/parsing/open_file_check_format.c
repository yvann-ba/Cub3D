/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_check_format.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:37:56 by lauger            #+#    #+#             */
/*   Updated: 2024/09/20 11:24:20 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool    has_extenssion(char *filename, char *extenssion)
{
	size_t  len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	if (ft_strcmp(filename + len - 4, extenssion) == 0)
		return (true);
	return (false);
}

int    open_file(char *file, t_data *data)
{
	int     fd;
	
	if (!file || !data)
		return (-1);
	if (has_extenssion(file, ".cub") == false)
	{
		printf(RED"Error:\nFailed to open file:"
			WHITE" file must have .cub extenssion\n");
		free(data->c_int_rgb);
		free(data->f_int_rgb);
		free(data);
		exit(0);
	}
	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
	{
		printf(RED"Error:\nFailed to open file:"
			WHITE" %s\n", strerror(errno));
		free(data->c_int_rgb);
		free(data->f_int_rgb);
		free(data);
		exit (0);
	}
	return (fd);
}