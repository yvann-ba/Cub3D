/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_file_data_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:42:57 by lauger            #+#    #+#             */
/*   Updated: 2024/09/05 11:41:28 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int  is_in_rang(int nb[6], int start, int end)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if (!((nb[i] >= start && nb[i] <= end)))
			return (1);
		i++;
	}
	return (0);
}

static void check_and_store_calor_values(char **f_tab, char ** c_tab, t_data *data)
{
	int     tab_num[6];

	if (!f_tab || !c_tab || !data)
		return ;
	tab_num[0] = ft_atoi_base(f_tab[0], "0123456789");
	tab_num[1] = ft_atoi_base(f_tab[1], "0123456789");
	tab_num[2] = ft_atoi_base(f_tab[2], "0123456789");
	tab_num[3] = ft_atoi_base(c_tab[0], "0123456789");
	tab_num[4] = ft_atoi_base(c_tab[1], "0123456789");
	tab_num[5] = ft_atoi_base(c_tab[2], "0123456789");
	if (is_in_rang(tab_num, 0, 255) == 1)
	{
		ft_printf(RED "Error:\nFile format is incorect:" WHITE" rgb values must be between 0 and 255\n");
		ft_free_tab(f_tab);
		ft_free_tab(c_tab);
		clean_exit(data);
	}
	data->f_rgb->red = tab_num[0];
	data->f_rgb->green = tab_num[1];
	data->f_rgb->blue = tab_num[2];
	data->c_rgb->red = tab_num[3];
	data->c_rgb->green = tab_num[4];
	data->c_rgb->blue = tab_num[5];
}

static int  take_colors_value(t_read_file *rf)
{
	char    *f_str;
	char    *c_str;
	char    **f_tab;
	char    **c_tab;

	if (!rf)
		return (-1);
	f_str = ft_substr(rf->tab_content[4], 2, ft_strlen(rf->tab_content[4]) -2);
	c_str = ft_substr(rf->tab_content[5], 2, ft_strlen(rf->tab_content[5]) -2);
	if (c_str == NULL || f_str == NULL)
		return (-1);
	f_tab = ft_split(f_str, ',');
	c_tab = ft_split(c_str, ',');
	if (f_tab == NULL || c_tab == NULL)
	{
		free(f_str);
		free(c_str);
		return (-1);
	}
	// print_2d_array(f_tab, 3);    
	// print_2d_array(c_tab, 3);
	free(f_str);
	free(c_str);
	check_and_store_calor_values(f_tab, c_tab, rf->data);
	return (0);
}

void    grab_color(t_data *data)
{
	if (!data)
		return ;
	if (check_line(data->read_file, "F ", 4, 2) != 0
		|| check_line(data->read_file, "C ", 5, 2) != 0)
		{
			ft_printf(RED "Error:\nFile format is incorect\n" WHITE);
			clean_exit(data);
		}
	take_colors_value(data->read_file);
	return ;
}
