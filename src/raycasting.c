#include "cub3d.h"


void calculate_ray(t_ray *ray, int x)
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
}

int render_next_frame(t_ray *ray)
{
    int x;
    int i;
    x = 0;
    i = 0;

    unsigned int **buffer;

    buffer = (unsigned int **)malloc(SCREEN_HEIGHT * sizeof(unsigned int *));
    if (buffer == NULL)
        return (1);
    while (i < SCREEN_HEIGHT)
    {
        buffer[i] = (unsigned int *)malloc(SCREEN_WIDTH * sizeof(unsigned int *));
        if (buffer == NULL)
            return (1);
        i++;
    }

    while (x < SCREEN_WIDTH)
    {
        calculate_ray(ray, x);
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

        
        // //texturing calculations
        // int tex_num = ray->int_map[ray->map_x][ray->map_y] - 1; //1 subtracted from it so that texture 0 can be used!

        // //calculate value of wallX
        // double wall_x; //where exactly the wall was hit
        // if (ray->side == 0) wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
        // else           wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
        // wall_x -= floor((wall_x));

        // //x coordinate on the texture
        // int tex_x;
        // tex_x = (int)(wall_x * (double)TEX_WIDTH);
        // if(ray->side == 0 && ray->ray_dir_x > 0) tex_x = TEX_WIDTH - tex_x - 1;
        // if(ray->side == 1 && ray->ray_dir_y < 0) tex_x = TEX_WIDTH - tex_x - 1;

        //             // How much to increase the texture coordinate per screen pixel
        // double step = 1.0 * TEX_HEIGHT / ray->line_height;
        // // Starting texture coordinate
        // double tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
        // for(int y = ray->draw_start; y < ray->draw_end; y++)
        // {
        //     // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        //     int tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
        //     tex_pos += step;
        //     int color = texture[0][TEX_HEIGHT * tex_y + tex_x];
        //     //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        //     if(ray->side == 1) color = (color >> 1) & 8355711;
        //     buffer[y][x] = color;
        // }

        put_ray_colors(ray, &x);
		x++;
	}
    // for(int y = 0; y < SCREEN_HEIGHT; y++)
    // {
    //     for(int x = 0; x < SCREEN_WIDTH; x++)
    //     {
    //         mlx_pixel_put(ray->mlx, ray->mlx_win, x, y, 0xE5D9F2)
    //     }
    // }
    // for(int y = 0; y < SCREEN_HEIGHT; y++) for(int x = 0; x < SCREEN_WIDTH; x++) buffer[y][x] = 0;
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

void put_ray_colors(t_ray *ray, int *x)
{
    int i;

    if (ray->int_map[ray->map_x][ray->map_y] == 1)
        ray->wall_color = 0xCDC1FF;
    if (ray->side == 1)
        ray->wall_color = 0xF5EFFF;
    i = ray->draw_start;
    while(i < ray->draw_end)
    {
        ray->addr[i * ray->line_length / 4 + *x] = ray->wall_color;
        i++;
    }
    i = ray->draw_end;
    ray->floor_color = 0xA594F9;
    while(i < SCREEN_HEIGHT)
    {
        ray->addr[i * ray->line_length / 4 + *x] = ray->floor_color;
        i++;
    }
    i = ray->draw_start;
    ray->ceilling_color = 0xE5D9F2;
    while(i > 0)
    {
        ray->addr[i * ray->line_length / 4 + *x] = ray->ceilling_color;
        i--;
    }
}
