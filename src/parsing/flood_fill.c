/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:22:10 by lauger            #+#    #+#             */
/*   Updated: 2024/09/26 10:38:40 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	replace_space_to_wall(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (!data)
		return (-1);
	while (data->map[i] != NULL)
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] == ' ')
				data->map[i][j] = '1';
			j++;
		}
		i++;
	}
	return (0);
}

static int	is_invalid(char **c_map, int x, int y)
{
	if (y > (int)ft_strlen(c_map[x]))
	{
		return (1);
	}
	if (c_map[x] == NULL || c_map[x][y] == '\0')
	{
		return (1);
	}
	return (0);
}

int	flood_fill(char **c_map, int x, int y)
{
	if (c_map[x] == NULL || y < 0 || c_map[x][y] == '\0')
	{
		return (1);
	}
	if (c_map[x][y] == '1')
		return (1);
	if (c_map[x][y] == '0')
	{
		if (is_invalid(c_map, x - 1, y)
			|| is_invalid(c_map, x + 1, y)
			|| is_invalid(c_map, x, y - 1)
			|| is_invalid(c_map, x, y + 1))
			return (-1);
		c_map[x][y] = '1';
	}
	flood_fill(c_map, x + 1, y);
	flood_fill(c_map, x - 1, y);
	flood_fill(c_map, x, y + 1);
	flood_fill(c_map, x, y - 1);
	return (0);
}

void	manage_utilization_flood_fill(t_data *data, char **c_map)
{
	int	i;
	int	j;

	i = 0;
	while (c_map[i] != NULL)
	{
		j = 0;
		while (c_map[i][j] != '\0')
		{
			if (flood_fill(c_map, i, j) == -1)
			{
				ft_putstr_fd(RED"Error:\nInvalid Map:"
					WHITE" must be surrounded by walls\n", 2);
				ft_free_tab(c_map);
				pars_clean_exit(data);
			}
			j++;
		}
		i++;
	}
}
