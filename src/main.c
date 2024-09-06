#include "cub3d.h"

int main(int ac, char **av)
{
    t_ray *ray;
    int i;

    (void)ac;
    (void)av;
    ray = (t_ray *)malloc(sizeof(t_ray));
    if (!ray)
    {
        ft_printf("Error\nmalloc() failed\n", 2);
        exit(1);
    }
    init_ray(ray);
    ray->mlx = mlx_init();
    ray->mlx_win = mlx_new_window(ray->mlx, ray->screen_width, ray->screen_height, "Cub3D");
    if (!ray->mlx_win)
    {
        ft_printf("Error\nmlx_new_window() failed\n", 2);
        exit(1);
    }
    ray->img = mlx_new_image(ray->mlx, ray->screen_width, ray->screen_height);

    i = 0;
    while (i < ray->screen_height)
    {
        ray->camera_x = 2 * i / (double)ray->screen_width - 1;
        ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
        ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
        ray->map_x = (int)ray->pos_x;
        ray->map_y = (int)ray->pos_y;
        if (ray->ray_dir_x == 0)
            ray->delta_dist_x = 1e30;
        else
            ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
        if (ray->ray_dir_y == 0)
            ray->delta_dist_y = 1e30;
        else
            ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
        if (ray->ray_dir_x < 0)
        {
            ray->step_x = -1;
            ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
        }
        else
        {
            ray->step_x = 1;
            ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
        }
        if (ray->ray_dir_y < 0)
        {
            ray->step_y = -1;
            ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
        }
        else
        {
            ray->step_y = 1;
            ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
        }
        while (ray->hit == 0)
        {
            if (ray->side_dist_x < ray->side_dist_y)
            {
                ray->side_dist_x += ray->delta_dist_x;
                ray->map_x += ray->step_x;
                ray->side = 0;
            }
            else
            {
                ray->side_dist_y += ray->delta_dist_y;
                ray->map_y += ray->step_y;
                ray->side = 1;
            }
            if (ray->map[ray->map_x][ray->map_y] > 0)
                ray->hit = 1;
        }
        i++;
    }
    mlx_loop(ray->mlx);
}
