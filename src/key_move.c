#include "cub3d.h"

int move_player(int keycode, t_ray *ray)
{
	if (keycode == 126 || keycode == 13) // Up arrow or W
	{
		if (ray->map[(int)(ray->pos_x + ray->dir_x * ray->move_speed)][(int)(ray->pos_y)] == 0)
			ray->pos_x += ray->dir_x * ray->move_speed;
		if (ray->map[(int)(ray->pos_x)][(int)(ray->pos_y + ray->dir_y * ray->move_speed)] == 0)
			ray->pos_y += ray->dir_y * ray->move_speed;
	}
	if (keycode == 125 || keycode == 1) // Down arrow or S
	{
		if (ray->map[(int)(ray->pos_x - ray->dir_x * ray->move_speed)][(int)(ray->pos_y)] == 0)
			ray->pos_x -= ray->dir_x * ray->move_speed;
		if (ray->map[(int)(ray->pos_x)][(int)(ray->pos_y - ray->dir_y * ray->move_speed)] == 0)
			ray->pos_y -= ray->dir_y * ray->move_speed;
	}
	return (0);
}

int rotate_player(int keycode, t_ray *ray)
{
	if (keycode == 124 || keycode == 2) // Right arrow or D
	{
		double oldDirX = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(-ray->rot_speed) - ray->dir_y * sin(-ray->rot_speed);
		ray->dir_y = oldDirX * sin(-ray->rot_speed) + ray->dir_y * cos(-ray->rot_speed);
		double oldPlaneX = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(-ray->rot_speed) - ray->plane_y * sin(-ray->rot_speed);
		ray->plane_y = oldPlaneX * sin(-ray->rot_speed) + ray->plane_y * cos(-ray->rot_speed);
	}
	if (keycode == 123 || keycode == 0) // Left arrow or A
	{
		double oldDirX = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(ray->rot_speed) - ray->dir_y * sin(ray->rot_speed);
		ray->dir_y = oldDirX * sin(ray->rot_speed) + ray->dir_y * cos(ray->rot_speed);
		double oldPlaneX = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(ray->rot_speed) - ray->plane_y * sin(ray->rot_speed);
		ray->plane_y = oldPlaneX * sin(ray->rot_speed) + ray->plane_y * cos(ray->rot_speed);
	}
	return (0);
}

int key_hook(int keycode, t_ray *ray)
{
	move_player(keycode, ray);
	rotate_player(keycode, ray);

	if (keycode == 65307)
		clean_close_windows(ray->data);

	return (0);
}
