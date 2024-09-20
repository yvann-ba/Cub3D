/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_file_data_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 09:42:57 by lauger            #+#    #+#             */
/*   Updated: 2024/09/20 11:10:59 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_in_rang(int nb[6], int start, int end)
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

static void	check_and_store_calor_values(char **f_tab, char ** c_tab, t_data *data)
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
	if (is_in_rang(tab_num, 0, 255) == 1)
	{
		ft_putstr_fd(RED "EEError:\nFile format is incorect:" WHITE" rgb values must be between 0 and 255\n", 2);
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

static int	take_colors_value(t_read_file *rf, int p_floor, int p_ceiling)
{
	char	*f_str;
	char	*c_str;
	char	**f_tab;
	char	**c_tab;

	if (!rf)
		return (-1);
	f_str = ft_substr(rf->tab_content[p_floor], 2, ft_strlen(rf->tab_content[p_floor]) -2);
	c_str = ft_substr(rf->tab_content[p_ceiling], 2, ft_strlen(rf->tab_content[p_ceiling]) -2);
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
	if (ft_tab_len(f_tab) != 3 || ft_tab_len(c_tab) != 3)
	{
		ft_putstr_fd(RED"Error:\nBad Syntax:" WHITE" value rgb requiere 3 values (value2,value2,value3)\n", 2);
		ft_free_tab(f_tab);
		ft_free_tab(c_tab);
		pars_clean_exit(rf->data);
	}
	check_and_store_calor_values(f_tab, c_tab, rf->data);
	return (0);
}

// void	grab_color(t_data *data)
// {
// 	if (!data)
// 		return ;
// 	if (check_line(data->read_file, "F ", 4, 2) != 0
// 		|| check_line(data->read_file, "C ", 5, 2) != 0)
// 		{
// 			ft_putstr_fd(RED "Error:\nFile format is incorect\n" WHITE, 2);
// 			pars_clean_exit(data);
// 		}
// 	take_colors_value(data->read_file);
// 	printf(MAGENTA"color->floor : %d, %d, %d\n", data->f_int_rgb->red, data->f_int_rgb->green, data->f_int_rgb->blue);
// 	printf(MAGENTA"color->ceiling : %d, %d, %d\n", data->c_int_rgb->red, data->c_int_rgb->green, data->c_int_rgb->blue);
// 	data->f_hex_rgb = convert_rgb_to_hex(data->f_int_rgb->red, data->f_int_rgb->green, data->f_int_rgb->blue);
// 	printf("\n");
// 	data->c_hex_rgb = convert_rgb_to_hex(data->c_int_rgb->red, data->c_int_rgb->green, data->c_int_rgb->blue);
// 	printf(BLUE"Finaly floor : %s\n", data->f_hex_rgb);
// 	printf(BLUE"Finaly ceiling : %s\n", data->c_hex_rgb);
// 	return ;
// }

static int	search_id_color(t_data *data, char *id)
{
	int	i;
	int	p_color;

	i = 0;
	p_color = -1;
	while (data->read_file->tab_content[i])
	{
		if (check_line(data->read_file, id, i, 1) == -2)
		{
			ft_putstr_fd(RED "Error:\nFFile format is incorect\n" WHITE, 2);
			pars_clean_exit(data);
		}
		else if (check_line(data->read_file, id, i, 1) == 0)
		{
			p_color = i;
			break ;
		}

		i++;
	}
	return (p_color);
}

int parseHex(char* input){
	int result = 0;
	while(input && *input){
		if(*input >= '0' && *input <= '9'){
			result <<= 4;
			result+= *input - '0';
		}
		if(*input >= 'a' && *input <= 'f'){
			result <<= 4;
			result+= *input - 'a'+10;
		}
		if(*input >= 'A' && *input <= 'F'){
			result <<= 4;
			result+= *input - 'A'+10;
		} 
		input++;
	}
	return result;
}

void	grab_color(t_data *data)
{
	if (!data)
		return ;
	int p_floor = search_id_color(data, "F ");
	int p_ceiling = search_id_color(data, "C ");
	if (p_floor == -1 || p_ceiling == -1)
	{
		ft_putstr_fd(RED "Error:\nFile format is incorect:"WHITE " there are not value flor r ceilling\n", 2);
		pars_clean_exit(data);
	}
	take_colors_value(data->read_file, p_floor, p_ceiling);
	//data->f_hex_rgb = convert_rgb_to_hex(data->f_int_rgb->red, data->f_int_rgb->green, data->f_int_rgb->blue);
	//data->c_hex_rgb = convert_rgb_to_hex(data->c_int_rgb->red, data->c_int_rgb->green, data->c_int_rgb->blue);
	// printf(GREEN"%d, %d, %d\n"WHITE, data->f_int_rgb->red, data->f_int_rgb->green, data->f_int_rgb->blue);
	data->f_hex_rgb = (data->f_int_rgb->red << 16) + (data->f_int_rgb->green << 8) + (data->f_int_rgb->blue);
	data->c_hex_rgb = (data->c_int_rgb->red << 16) + (data->c_int_rgb->green << 8) + (data->c_int_rgb->blue);
	// printf(BLUE"Finaly floor : %lld\n"WHITE, data->f_hex_rgb);
	// printf(BLUE"Finaly ceiling :%lld\n"WHITE, data->c_hex_rgb);
	return ;
}
