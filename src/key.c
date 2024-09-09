#include "cub3d.h"

int key_hook(int keycode, t_ray *ray)
{
    // Gestion des touches pour le déplacement et la rotation
    if (keycode == 126 || keycode == 13) // Flèche haut ou W
    {
        if (ray->map[(int)(ray->pos_x + ray->dir_x * ray->move_speed)][(int)(ray->pos_y)] == 0)
            ray->pos_x += ray->dir_x * ray->move_speed;
        if (ray->map[(int)(ray->pos_x)][(int)(ray->pos_y + ray->dir_y * ray->move_speed)] == 0)
            ray->pos_y += ray->dir_y * ray->move_speed;
    }
    if (keycode == 125 || keycode == 1) // Flèche bas ou S
    {
        if (ray->map[(int)(ray->pos_x - ray->dir_x * ray->move_speed)][(int)(ray->pos_y)] == 0)
            ray->pos_x -= ray->dir_x * ray->move_speed;
        if (ray->map[(int)(ray->pos_x)][(int)(ray->pos_y - ray->dir_y * ray->move_speed)] == 0)
            ray->pos_y -= ray->dir_y * ray->move_speed;
    }
    if (keycode == 124 || keycode == 2) // Flèche droite ou D
    {
        double oldDirX = ray->dir_x;
        ray->dir_x = ray->dir_x * cos(-ray->rot_speed) - ray->dir_y * sin(-ray->rot_speed);
        ray->dir_y = oldDirX * sin(-ray->rot_speed) + ray->dir_y * cos(-ray->rot_speed);
        double oldPlaneX = ray->plane_x;
        ray->plane_x = ray->plane_x * cos(-ray->rot_speed) - ray->plane_y * sin(-ray->rot_speed);
        ray->plane_y = oldPlaneX * sin(-ray->rot_speed) + ray->plane_y * cos(-ray->rot_speed);
    }
    if (keycode == 123 || keycode == 0) // Flèche gauche ou A
    {
        double oldDirX = ray->dir_x;
        ray->dir_x = ray->dir_x * cos(ray->rot_speed) - ray->dir_y * sin(ray->rot_speed);
        ray->dir_y = oldDirX * sin(ray->rot_speed) + ray->dir_y * cos(ray->rot_speed);
        double oldPlaneX = ray->plane_x;
        ray->plane_x = ray->plane_x * cos(ray->rot_speed) - ray->plane_y * sin(ray->rot_speed);
        ray->plane_y = oldPlaneX * sin(ray->rot_speed) + ray->plane_y * cos(ray->rot_speed);
    }

    if (keycode == 53) 
        exit(0);

    return (0);
}
