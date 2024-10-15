/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:46:53 by ybarbot           #+#    #+#             */
/*   Updated: 2024/10/15 14:02:10 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_max_lenght(char **map)
{
	int	i;
	int	j;
	int	max_lenght;

	i = 0;
	max_lenght = 0;
	if (!map)
		return (-1);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (j > max_lenght)
				max_lenght = j;
			j++;
		}
		i++;
	}
	return (max_lenght);
}

int	**allocate_int_map(t_data *data)
{
	int	**int_map;
	int	i;

	data->map_width = find_max_lenght(data->map) + 1;
	if (!data->map_width)
		pars_clean_exit(data);
	data->map_height = ft_tab_len(data->map);
	int_map = (int **)malloc(data->map_height * sizeof(int *));
	if (!int_map)
	{
		ft_printf("Error\nmalloc() failed\n", 2);
		exit(1);
	}
	i = 0;
	while (i < data->map_height)
	{
		int_map[i] = (int *)malloc(data->map_width * sizeof(int));
		if (!int_map[i])
		{
			ft_printf("Error\nmalloc() failed\n", 2);
			exit(1);
		}
		i++;
	}
	return (int_map);
}

void	fill_map_holes(t_data *data, int **int_map, int *x, int *y)
{
	while ((*x) < data->map_width)
	{
		int_map[*y][*x] = -1;
		(*x)++;
	}
	(*y)++;
}

void	parse_map(t_ray *ray, t_data *data, int **int_map)
{
	int	y;
	int	x;
	int	size_line;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		size_line = (int)ft_strlen(data->map[y]);
		while (x < size_line)
		{
			if (data->map[y][x] == '1')
				int_map[y][x] = 1;
			else if (data->map[y][x] == '0')
				int_map[y][x] = 0;
			else if (data->map[y][x] == 'N' || data->map[y][x] == 'S' \
			|| data->map[y][x] == 'E' || data->map[y][x] == 'W')
			{
				set_player_position(ray, x, y, data->map[y][x]);
				int_map[y][x] = 0;
			}
			x++;
		}
		fill_map_holes(data, int_map, &x, &y);
	}
}
