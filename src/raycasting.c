#include "cub3d.h"

int render_next_frame(t_ray *ray)
{
    int x = 0;

    // Reset the image before each frame
    mlx_clear_window(ray->mlx, ray->mlx_win);

    // Raycasting logic for each column of the screen
    while (x < ray->screen_width)
    {
        ray->camera_x = 2 * x / (double)ray->screen_width - 1;
        ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
        ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
        ray->map_x = (int)ray->pos_x;
        ray->map_y = (int)ray->pos_y;

        // Reset hit for each ray
        ray->hit = 0;

        // Calculate delta_dist (for the distance between intersections)
        ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1 / ray->ray_dir_x);
        ray->delta_dist_y = (ray->ray_dir_y == 0) ? 1e30 : fabs(1 / ray->ray_dir_y);

        // Calculate initial distances (side_dist) and direction (step)
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

        // DDA algorithm to find where the ray hits a wall
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
            // If the ray hits a wall
            if (ray->map[ray->map_x][ray->map_y] > 0)
                ray->hit = 1;
        }

        // Calculate the projected distance of the wall on the camera plane
        if (ray->side == 0)
            ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
        else
            ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;

        // Calculate the height of the line to draw on the screen
        ray->line_height = (int)(ray->screen_height / ray->perp_wall_dist);

        // Calculate the start and end points to draw the line
        ray->draw_start = -ray->line_height / 2 + ray->screen_height / 2;
        if (ray->draw_start < 0)
            ray->draw_start = 0;
        ray->draw_end = ray->line_height / 2 + ray->screen_height / 2;
        if (ray->draw_end >= ray->screen_height)
            ray->draw_end = ray->screen_height - 1;

        // Choose the color (simplified example: white wall)
        int color = (ray->map[ray->map_x][ray->map_y] == 1) ? 0xFFFFFF : 0x000000;

        // Reduce brightness for side walls
        if (ray->side == 1)
            color = color / 2;

        // Draw the vertical line (wall)
        for (int y = ray->draw_start; y < ray->draw_end; y++)
        {
            ray->addr[y * ray->line_length / 4 + x] = color;  // Write to the memory image
        }

        x++;
    }

    // Display the final image
    mlx_put_image_to_window(ray->mlx, ray->mlx_win, ray->img, 0, 0);

    // Time management (for FPS)
    ray->old_time = ray->time;
    ray->time = get_current_time_millis();
    ray->frame_time = (ray->time - ray->old_time) / 1000.0;

    // Avoid division by zero and display the FPS
    if (ray->frame_time > 0)
    {
        //printf("FPS: %f\n", 1.0 / ray->frame_time);
    }

    // Calculate the movement and rotation speed based on the frame time
    ray->move_speed = ray->frame_time * 5.0;  // Constant in squares/second
    ray->rot_speed = ray->frame_time * 3.0;   // Constant in radians/second

    return (0);
}
