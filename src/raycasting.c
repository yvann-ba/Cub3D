#include "cub3d.h"

int render_next_frame(t_ray *ray)
{
    int x;

    x = 0;
    while (x < SCREEN_WIDTH)
    {
        ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
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
        ray->hit = 0;
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
            if (ray->int_map[ray->map_x][ray->map_y] > 0)
                ray->hit = 1;
        }
        if (ray->side == 0)
            ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
        else
            ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);

        ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
        ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
        if (ray->draw_start < 0)
            ray->draw_start = 0;
        ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
        if (ray->draw_end >= SCREEN_HEIGHT)
            ray->draw_end = SCREEN_HEIGHT - 1;
        if (ray->int_map[ray->map_x][ray->map_y] == 1)
            ray->wall_color = 0xFFFFFF;
        if (ray->side == 1)
            ray->wall_color = ray->wall_color / 2;
        for (int q = ray->draw_start; q < ray->draw_end; q++)
            ray->addr[q * ray->line_length / 4 + x] = ray->wall_color;

        ray->ceilling_color = 0xFF676FF;
        ray->floor_color = 0xFF151F;
        for (int d = ray->draw_end; d < SCREEN_HEIGHT; d++)
            ray->addr[d * ray->line_length / 4 + x] = ray->ceilling_color;
        for (int b = ray->draw_start; b > 0; b--)
            ray->addr[b * ray->line_length / 4 + x] = ray->floor_color;
		x++;
	}
    ray->old_time = ray->time;
    ray->time = get_current_time_millis();
    ray->frame_time = (ray->time - ray->old_time) / 1000.0;
    if (ray->frame_time > 0)
        //printf("FPS: %f\n", 1.0 / ray->frame_time);
    mlx_put_image_to_window(ray->mlx, ray->mlx_win, ray->img, 0, 0);
    ray->move_speed = ray->frame_time * 5.0;
    ray->rot_speed = ray->frame_time * 3.0;
	return (0);
}
