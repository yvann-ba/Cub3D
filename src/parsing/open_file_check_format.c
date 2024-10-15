/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_check_format.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:39:04 by lauger            #+#    #+#             */
/*   Updated: 2024/09/24 14:16:24 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	has_extension(char *filename, char *extension)
{
	size_t	len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	if (ft_strcmp(filename + len - 4, extension) == 0)
		return (true);
	return (false);
}

static int	handle_open(char *file, t_data *data)
{
	int	fd;

	fd = open(file, __O_DIRECTORY);
	if (fd != -1)
	{
		printf(RED"Error:\nFailed to open file: is folder\n"
			WHITE" %s\n", strerror(errno));
		free(data->c_int_rgb);
		free(data->f_int_rgb);
		free(data);
		close(fd);
		exit (0);
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

int	open_file(char *file, t_data *data)
{
	int	fd;

	if (!file || !data)
		return (-1);
	if (has_extension(file, ".cub") == false)
	{
		printf(RED"Error:\nFailed to open file:"
			WHITE" file must have .cub extension\n");
		free(data->c_int_rgb);
		free(data->f_int_rgb);
		free(data);
		exit(0);
	}
	fd = handle_open(file, data);
	return (fd);
}
