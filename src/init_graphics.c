#include "cub3d.h"

void init_ray(t_ray *ray)
{
    ray->screen_width = 640;
    ray->screen_height = 480;
    ray->screen_half_width = ray->screen_width / 2;
    ray->screen_half_height = ray->screen_height / 2;
    ray->render_delay = 30; // milliseconds
    ray->player_fov = 60.0; // degrees
    ray->player_half_fov = ray->player_fov / 2;
    ray->pos_x = 2.0;
    ray->pos_y = 2.0;
    ray->player_angle = 90.0;
    ray->ray_increment_angle = ray->player_fov / ray->screen_width;
    ray->raycasting_precision = 64;
    ray->dir_x = -1.0;
    ray->dir_y = 0;
    ray->plane_x = 0;
    ray->plane_y = 0.66;
    ray->time = 0;
    ray->old_time = 0;
    ray->hit = 0;
}

void parse_map(t_ray *ray, char **char_map, int **int_map, int width, int height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (char_map[y][x] == '1')
                int_map[y][x] = 1;  // Wall
            else if (char_map[y][x] == '0')
                int_map[y][x] = 0;  // Empty space
            else if (char_map[y][x] == 'N' || char_map[y][x] == 'S' || char_map[y][x] == 'E' || char_map[y][x] == 'W')
            {
                // Position the player
                ray->pos_x = x + 0.5;
                ray->pos_y = y + 0.5;

                // Set the player's direction based on the character
                if (char_map[y][x] == 'N') {
                    ray->dir_x = 0;
                    ray->dir_y = -1;
                    ray->plane_x = 0.66;  // Camera plane for FOV
                    ray->plane_y = 0;
                }
                else if (char_map[y][x] == 'S') {
                    ray->dir_x = 0;
                    ray->dir_y = 1;
                    ray->plane_x = -0.66;
                    ray->plane_y = 0;
                }
                else if (char_map[y][x] == 'E') {
                    ray->dir_x = 1;
                    ray->dir_y = 0;
                    ray->plane_x = 0;
                    ray->plane_y = 0.66;
                }
                else if (char_map[y][x] == 'W') {
                    ray->dir_x = -1;
                    ray->dir_y = 0;
                    ray->plane_x = 0;
                    ray->plane_y = -0.66;
                }
                int_map[y][x] = 0;  // Player's initial position should be walkable
            }
        }
    }
}

int init_graphics(t_ray *ray)
{
    ray->mlx = mlx_init();
    if (!ray->mlx)
	{
		cleanup_graphics(ray);
		ft_printf("Error initializing mlx");
		return (1);
	}
    ray->mlx_win = mlx_new_window(ray->mlx, ray->screen_width, ray->screen_height, "Cub3D");
	if (!ray->mlx_win)
	{
		cleanup_graphics(ray);
		ft_printf("Error creating window");
		return (1);
	}
    ray->img = mlx_new_image(ray->mlx, ray->screen_width, ray->screen_height);
    if (!ray->img)
    {
        cleanup_graphics(ray);
        ft_printf("Error creating image");
        return (1);
    }
    //ray->addr = (int *)mlx_get_data_addr(ray->img, &ray->bpp, &ray->line_length, &ray->endian);
    return (0);
}
