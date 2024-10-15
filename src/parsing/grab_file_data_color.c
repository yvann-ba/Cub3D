/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_file_data_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:42:57 by lauger            #+#    #+#             */
/*   Updated: 2024/09/24 13:22:04 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_in_range(int nb[6], int start, int end)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (!((nb[i] >= start && nb[i] <= end)))
			return (1);
		i++;
	}
	return (0);
}

static int	search_id_color(t_data *data, char *id)
{
	int	i;
	int	p_color;

	i = 0;
	p_color = -1;
	while (data->rf->tab_content[i])
	{
		if (check_line(data->rf, id, i, 1) == -2)
		{
			ft_putstr_fd(RED "Error:\nFile format is incorrect\n" WHITE, 2);
			pars_clean_exit(data);
		}
		else if (check_line(data->rf, id, i, 1) == 0)
		{
			p_color = i;
			break ;
		}
		i++;
	}
	return (p_color);
}

void	grab_color(t_data *data)
{
	int	p_ceiling;
	int	p_floor;

	if (!data)
		return ;
	p_floor = search_id_color(data, "F ");
	p_ceiling = search_id_color(data, "C ");
	if (p_floor == -1 || p_ceiling == -1)
	{
		ft_putstr_fd(RED "Error:\nFile format is incorrect:"
			WHITE" there are no floor or ceilling values\n"WHITE, 2);
		pars_clean_exit(data);
	}
	take_colors_value(data->rf, p_floor, p_ceiling);
	data->f_hex_rgb = (data->f_int_rgb->red << 16)
		+ (data->f_int_rgb->green << 8) + (data->f_int_rgb->blue);
	data->c_hex_rgb = (data->c_int_rgb->red << 16)
		+ (data->c_int_rgb->green << 8) + (data->c_int_rgb->blue);
	return ;
}
