/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:41:02 by lauger            #+#    #+#             */
/*   Updated: 2024/09/23 10:55:01 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	add_eof_content(t_read_file *rf)
{
	if (rf->bytes_read < 0)
	{
		perror("read");
		free(rf->str_content);
		pars_clean_exit(rf->data);
	}
	if (rf->str_content != NULL)
		rf->str_content[rf->total_size] = '\0';
	else
	{
		rf->str_content = malloc(1);
		if (rf->str_content == NULL)
		{
			perror("malloc");
			pars_clean_exit(rf->data);
		}
		rf->str_content[0] = '\0';
	}
}

static t_read_file	*init_rf(t_data *data, int fd)
{
	t_read_file	*rf;

	rf = malloc(sizeof(t_read_file));
	if (rf == NULL)
	{
		perror("malloc");
		pars_clean_exit(data);
	}
	rf->p_north = NULL;
	rf->p_south = NULL;
	rf->p_west = NULL;
	rf->p_east = NULL;
	rf->str_content = NULL;
	rf->total_size = 0;
	rf->data = data;
	if (fd < 0)
	{
		perror("Invalid file descriptor");
		free(rf);
		pars_clean_exit(rf->data);
	}
	return (rf);
}

t_read_file	*read_file_to_string(int fd, t_data *data)
{
	t_read_file	*rf;
	char		*new_content;

	rf = init_rf(data, fd);
	rf->bytes_read = read(fd, rf->buffer, sizeof(rf->buffer));
	while (rf->bytes_read > 0)
	{
		rf->new_size = rf->total_size + rf->bytes_read;
		new_content = ft_realloc(rf->str_content, rf->new_size + 1,
				ft_strlen(rf->str_content));
		if (new_content == NULL)
		{
			perror("realloc");
			free(rf->str_content);
			free(rf);
			pars_clean_exit(rf->data);
		}
		rf->str_content = new_content;
		ft_memcpy(rf->str_content + rf->total_size, rf->buffer, rf->bytes_read);
		rf->total_size += rf->bytes_read;
		rf->bytes_read = read(fd, rf->buffer, sizeof(rf->buffer));
	}
	add_eof_content(rf);
	rf->data = data;
	return (rf);
}
