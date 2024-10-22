#include "cub3d.h"

void	rotate_2(int keycode, t_ray *ray, double \
*old_dir_x, double *old_plane_x)
{
	if (keycode == 65361)
	{
		*old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(ray->rot_speed) \
		- ray->dir_y * sin(ray->rot_speed);
		ray->dir_y = *old_dir_x * sin(ray->rot_speed) \
		+ ray->dir_y * cos(ray->rot_speed);
		*old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(ray->rot_speed) \
		- ray->plane_y * sin(ray->rot_speed);
		ray->plane_y = *old_plane_x * sin(ray->rot_speed) \
		+ ray->plane_y * cos(ray->rot_speed);
	}
}

void	rotate_1(int keycode, t_ray *ray)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == 65363)
	{
		old_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(-ray->rot_speed) \
		- ray->dir_y * sin(-ray->rot_speed);
		ray->dir_y = old_dir_x * sin(-ray->rot_speed) \
		+ ray->dir_y * cos(-ray->rot_speed);
		old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(-ray->rot_speed) \
		- ray->plane_y * sin(-ray->rot_speed);
		ray->plane_y = old_plane_x * sin(-ray->rot_speed) \
		+ ray->plane_y * cos(-ray->rot_speed);
	}
	rotate_2(keycode, ray, &old_dir_x, &old_plane_x);
}

void	move_player_y(int keycode, t_ray *ray)
{
	double	new_pos_x;
	double	new_pos_y;

	if (keycode == 119)
	{
		new_pos_x = ray->pos_x + ray->dir_x * ray->move_speed;
		new_pos_y = ray->pos_y + ray->dir_y * ray->move_speed;
		if (ray->int_map[(int)new_pos_x][(int)(ray->pos_y)] == 0)
			ray->pos_x = new_pos_x;
		if (ray->int_map[(int)(ray->pos_x)][(int)new_pos_y] == 0)
			ray->pos_y = new_pos_y;
	}
	if (keycode == 115)
	{
		new_pos_x = ray->pos_x - ray->dir_x * ray->move_speed;
		new_pos_y = ray->pos_y - ray->dir_y * ray->move_speed;
		if (ray->int_map[(int)new_pos_x][(int)(ray->pos_y)] == 0)
			ray->pos_x = new_pos_x;
		if (ray->int_map[(int)(ray->pos_x)][(int)new_pos_y] == 0)
			ray->pos_y = new_pos_y;
	}
}

void	move_player_x(int keycode, t_ray *ray)
{
	double	new_pos_x;
	double	new_pos_y;

	if (keycode == 100)
	{
		new_pos_x = ray->pos_x + ray->dir_y * ray->move_speed;
		new_pos_y = ray->pos_y - ray->dir_x * ray->move_speed;
		if (ray->int_map[(int)new_pos_x][(int)(ray->pos_y)] == 0)
			ray->pos_x = new_pos_x;
		if (ray->int_map[(int)(ray->pos_x)][(int)new_pos_y] == 0)
			ray->pos_y = new_pos_y;
	}
	if (keycode == 97)
	{
		new_pos_x = ray->pos_x - ray->dir_y * ray->move_speed;
		new_pos_y = ray->pos_y + ray->dir_x * ray->move_speed;
		if (ray->int_map[(int)new_pos_x][(int)(ray->pos_y)] == 0)
			ray->pos_x = new_pos_x;
		if (ray->int_map[(int)(ray->pos_x)][(int)new_pos_y] == 0)
			ray->pos_y = new_pos_y;
	}
}

int	key_hook(int keycode, t_ray *ray)
{
	move_player(keycode, ray);
	rotate_1(keycode, ray);
	if (keycode == 65307)
		clean_close_windows(ray->data);
	return (0);
}
