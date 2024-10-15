/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_color_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:21:24 by lauger            #+#    #+#             */
/*   Updated: 2024/09/25 11:06:18 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_and_store_calor_values(char **f_tab,
	char **c_tab, t_data *data)
{
	int	tab_num[6];

	if (!f_tab || !c_tab || !data)
		return ;
	tab_num[0] = ft_atoi_base(f_tab[0], "0123456789");
	tab_num[1] = ft_atoi_base(f_tab[1], "0123456789");
	tab_num[2] = ft_atoi_base(f_tab[2], "0123456789");
	tab_num[3] = ft_atoi_base(c_tab[0], "0123456789");
	tab_num[4] = ft_atoi_base(c_tab[1], "0123456789");
	tab_num[5] = ft_atoi_base(c_tab[2], "0123456789");
	if (is_in_range(tab_num, 0, 255) == 1)
	{
		ft_putstr_fd(RED "Error:\nFile format is incorrect\n"WHITE, 2);
		ft_free_tab(f_tab);
		ft_free_tab(c_tab);
		pars_clean_exit(data);
	}
	ft_free_tab(f_tab);
	ft_free_tab(c_tab);
	data->f_int_rgb->red = tab_num[0];
	data->f_int_rgb->green = tab_num[1];
	data->f_int_rgb->blue = tab_num[2];
	data->c_int_rgb->red = tab_num[3];
	data->c_int_rgb->green = tab_num[4];
	data->c_int_rgb->blue = tab_num[5];
}

static void	is_value_conform(char **f_tab, char **c_tab, t_read_file *rf)
{
	if (ft_tab_len(f_tab) != 3 || ft_tab_len(c_tab) != 3)
	{
		ft_putstr_fd(RED"Error:\nBad Syntax:"
			WHITE" value rgb require 3 values (value1,value2,value3)\n", 2);
		ft_free_tab(f_tab);
		ft_free_tab(c_tab);
		pars_clean_exit(rf->data);
	}
	check_and_store_calor_values(f_tab, c_tab, rf->data);
}

int	take_colors_value(t_read_file *rf, int p_floor, int p_ceiling)
{
	char	*f_str;
	char	*c_str;
	char	**f_tab;
	char	**c_tab;

	if (!rf)
		return (-1);
	f_str = deblank(ft_substr(rf->tab_content[p_floor], 1,
				ft_strlen(rf->tab_content[p_floor]) - 1), 1);
	c_str = deblank(ft_substr(rf->tab_content[p_ceiling], 1,
				ft_strlen(rf->tab_content[p_ceiling]) - 1), 1);
	if (c_str == NULL || f_str == NULL)
		return (-1);
	f_tab = ft_split(f_str, ',');
	c_tab = ft_split(c_str, ',');
	if (f_tab == NULL || c_tab == NULL)
	{
		free(f_str);
		free(c_str);
		pars_clean_exit(rf->data);
	}
	free(f_str);
	free(c_str);
	is_value_conform(f_tab, c_tab, rf);
	return (0);
}
