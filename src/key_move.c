#include "cub3d.h"

int move_player(int keycode, t_ray *ray)
{
    if (keycode == 119) // W
    {
        if (ray->int_map[(int)(ray->pos_x + ray->dir_x * ray->move_speed)][(int)(ray->pos_y)] == 0)
            ray->pos_x += ray->dir_x * ray->move_speed;
        if (ray->int_map[(int)(ray->pos_x)][(int)(ray->pos_y + ray->dir_y * ray->move_speed)] == 0)
            ray->pos_y += ray->dir_y * ray->move_speed;
    }
    if (keycode == 115) // S
    {
        if (ray->int_map[(int)(ray->pos_x - ray->dir_x * ray->move_speed)][(int)(ray->pos_y)] == 0)
            ray->pos_x -= ray->dir_x * ray->move_speed;
        if (ray->int_map[(int)(ray->pos_x)][(int)(ray->pos_y - ray->dir_y * ray->move_speed)] == 0)
            ray->pos_y -= ray->dir_y * ray->move_speed;
    }
    if (keycode == 97) // A
    {
        if (ray->int_map[(int)(ray->pos_y + ray->dir_y * ray->move_speed)][(int)(ray->pos_x)] == 0)
        {
            printf("prout");
            ray->pos_y -= ray->dir_y * ray->move_speed;
        }
        if (ray->int_map[(int)(ray->pos_y)][(int)(ray->pos_x + ray->dir_x * ray->move_speed)] == 0)
            ray->pos_x -= ray->dir_x * ray->move_speed;
    }
    // if (keycode == 100) // D
    // {
    //     if (ray->int_map[(int)(ray->pos_x - ray->dir_x * ray->move_speed)][(int)(ray->pos_y)] == 0)
    //         ray->pos_x -= ray->dir_x * ray->move_speed;
    //     if (ray->int_map[(int)(ray->pos_x)][(int)(ray->pos_y - ray->dir_y * ray->move_speed)] == 0)
    //         ray->pos_y -= ray->dir_y * ray->move_speed;
    // }
    printf("Player moved to: (%f, %f)\n", ray->pos_x, ray->pos_y);
    return (0);
}

int rotate_player(int keycode, t_ray *ray)
{
    double old_dir_x;
    double old_plane_x;

    if (keycode == 65361) // Right arrow
    {
        old_dir_x = ray->dir_x;
        ray->dir_x = ray->dir_x * cos(-ray->rot_speed) - ray->dir_y * sin(-ray->rot_speed);
        ray->dir_y = old_dir_x * sin(-ray->rot_speed) + ray->dir_y * cos(-ray->rot_speed);
        old_plane_x = ray->plane_x;
        ray->plane_x = ray->plane_x * cos(-ray->rot_speed) - ray->plane_y * sin(-ray->rot_speed);
        ray->plane_y = old_plane_x * sin(-ray->rot_speed) + ray->plane_y * cos(-ray->rot_speed);
    }
    if (keycode == 65363) // Left arrow
    {
        old_dir_x = ray->dir_x;
        ray->dir_x = ray->dir_x * cos(ray->rot_speed) - ray->dir_y * sin(ray->rot_speed);
        ray->dir_y = old_dir_x * sin(ray->rot_speed) + ray->dir_y * cos(ray->rot_speed);
        old_plane_x = ray->plane_x;
        ray->plane_x = ray->plane_x * cos(ray->rot_speed) - ray->plane_y * sin(ray->rot_speed);
        ray->plane_y = old_plane_x * sin(ray->rot_speed) + ray->plane_y * cos(ray->rot_speed);
    }
    return (0);
}

int key_hook(int keycode, t_ray *ray)
{
	move_player(keycode, ray);
	rotate_player(keycode, ray);
    printf("%d\n", keycode);
	if (keycode == 65307)
		clean_close_windows(ray->data);

	return (0);
}
