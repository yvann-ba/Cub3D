#include "../cub3d.h"

void    pars_clean_exit(t_data *data)
{
	if (data->read_file->str_content)
		free(data->read_file->str_content);
	if (data->read_file->tab_content)
		ft_free_tab(data->read_file->tab_content);
	if (data->read_file->p_north)
		free(data->read_file->p_north);
	if (data->read_file->p_south)
		free(data->read_file->p_south);
	if (data->read_file->p_west)
		free(data->read_file->p_west);
	if (data->read_file->p_east)
		free(data->read_file->p_east);
	if (data->read_file)
		free(data->read_file);
	if (data->c_rgb)
		free(data->c_rgb);
	if (data->f_rgb)
		free(data->f_rgb);
	if (data->map)
		ft_free_tab(data->map);
	if (data)
		free(data);
	exit(0);
}

void    pars_clean_return(t_data *data)
{
	if (data->read_file->str_content)
		free(data->read_file->str_content);
	if (data->read_file->tab_content)
		ft_free_tab(data->read_file->tab_content);
	if (data->read_file->p_north)
		free(data->read_file->p_north);
	if (data->read_file->p_south)
		free(data->read_file->p_south);
	if (data->read_file->p_west)
		free(data->read_file->p_west);
	if (data->read_file->p_east)
		free(data->read_file->p_east);
	if (data->read_file)
		free(data->read_file);
	if (data->c_rgb)
		free(data->c_rgb);
	if (data->f_rgb)
		free(data->f_rgb);
	if (data->map)
		ft_free_tab(data->map);
	if (data)
		free(data);
	return ;
}