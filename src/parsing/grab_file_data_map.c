/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_file_data_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:55:41 by lauger            #+#    #+#             */
/*   Updated: 2024/09/06 11:38:17 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	**create_new_tab_from_n(char **tab, int n)
{
	int			original_size;
	int			new_size;
	char **		new_tab;
	int			i;
	
	i = 0;
	original_size = ft_tab_len(tab);
	if (n >= original_size || n < 0)
	{
		printf("Invalid starting index!\n");
		return NULL;
	}
	new_size = original_size - n;
	new_tab = ft_calloc((new_size + 1), sizeof(char *));
	if (!new_tab)
	{
		printf("Memory allocation failed!\n");
		return NULL;
	}
	while (i < new_size)
	{
		new_tab[i] = ft_strdup(tab[n + i]);
		i++;
	}
	new_tab[new_size] = NULL;
	return (new_tab);
}

static int	contains_only_these_caractere(char **map)
{
	int	i;
	int	j;

	if (!map)
		return (-1);
	i = 0;
	while (map[i])
	{
		j = 0;
		while(map[i][j] != 0)
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' '
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'O'
				&& map[i][j] != 'W')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_only_spaces_ones(char **map, int id, int sizeMap)
{
	int	i;

	if (!map || id < 0 || id > sizeMap || sizeMap <= 0 || !map[id])
 		return (1);
	i = 0;
	while (i < sizeMap)
	{
		if (map[id][i] != ' ' && map[id][i] != '1')
			return (1);
		i++;
	}
	return (0);
}

void	grab_map(t_data *data)
{
	if (!data)
		return ;
	data->map = create_new_tab_from_n(data->read_file->tab_content, 6);
	if (data->map == NULL)
	{
		ft_putstr_fd(RED"Error:\nmalloc failed"WHITE, 2);
		clean_exit(data);
	}
	print_2d_array(data->map, 15);
	if (contains_only_these_caractere(data->map) == 1)
	{
		ft_putstr_fd(RED"Error:\nincorect map format"WHITE" must be contains of '0' '1' SPACE 'N' 'S' 'W' 'O'\n", 2);
		clean_exit(data);
	}
	if (check_only_spaces_ones(data->map, 0, ft_tab_len(data->map)) == 1
		|| check_only_spaces_ones(data->map, ft_tab_len(data->map) - 1, ft_tab_len(data->map)) == 1)
	{
		ft_putstr_fd(RED"EError:\nincorect map format"WHITE" must be contains of '0' '1' SPACE 'N' 'S' 'W' 'O'\n", 2);
		clean_exit(data);
	}
}
