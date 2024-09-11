/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:22:10 by lauger            #+#    #+#             */
/*   Updated: 2024/09/09 13:38:53 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

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
	if (c_map[x] == NULL || c_map[x][y] == '\0')
	{
		return 1;
	}
	return 0;
}

int	flood_fill(char **c_map, int x, int y)
{
	if (c_map[x] == NULL || y < 0 || c_map[x][y] == '\0')
	{
		return (1);
	}
	if (c_map[x][y] == '1') {
		return (1);
	}
	if (c_map[x][y] == '0')
	{
		if (is_invalid(c_map, x - 1, y) ||
			is_invalid(c_map, x + 1, y) ||
			is_invalid(c_map, x, y - 1) ||
			is_invalid(c_map, x, y + 1)) {
			return (-1);
		}
		c_map[x][y] = '1';
	}
	flood_fill(c_map, x + 1, y);
	flood_fill(c_map, x - 1, y);
	flood_fill(c_map, x, y + 1);
	flood_fill(c_map, x, y - 1);
	return (0);
}
