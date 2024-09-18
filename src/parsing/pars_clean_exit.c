#include "../cub3d.h"

// void	free_mlx_images(t_data *data)
// {
// 	if (!data)
// 		return ;
// 	if (data->north)
// 		mlx_destroy_image(data->ray->mlx, data->north);
// 	if (data->south)
// 		mlx_destroy_image(data->ray->mlx, data->south);
// 	if (data->west)
// 		mlx_destroy_image(data->ray->mlx, data->west);
// 	if (data->east)
// 		mlx_destroy_image(data->ray->mlx, data->east);
// }

void	all_clean_exit(t_data *data)
{
	// if (data->north)
	// 	free(data->north);
	// if (data->south)
	// 	free(data->south);
	// if (data->west)
	// 	free(data->west);
	// if (data->east)
	// 	free(data->east);
	if (data->ray->img)
		mlx_destroy_image(data->ray->mlx, data->ray->img);
	if (data->ray->mlx)
		mlx_destroy_window(data->ray->mlx, data->ray->mlx_win);
	if (data->ray->mlx)
		mlx_destroy_display(data->ray->mlx);
	free(data->ray->mlx);
	ft_free_tab_int(data->ray->int_map, data->map_height);
	free(data->ray);
	pars_clean_exit(data);
}

void	pars_clean_exit(t_data *data)
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
	if (data->c_int_rgb)
		free(data->c_int_rgb);
	if (data->f_int_rgb)
		free(data->f_int_rgb);
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
	if (data->c_int_rgb)
		free(data->c_int_rgb);
	if (data->f_int_rgb)
		free(data->f_int_rgb);
	if (data->map)
		ft_free_tab(data->map);
	if (data)
		free(data);
	return ;
}