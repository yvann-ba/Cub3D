#include "cub3d.h"

long getTicks(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

int main(int ac, char **av)
{

    (void)ac;
    (void)av;
    t_ray *ray;
    int map_width = 6;
    int map_height = 5;

    // Exemple de carte avec le joueur face au nord
    char *char_map[] = {
        "111111",
        "100001",
        "10N001",
        "100001",
        "111111",
        NULL
    };

    // Allouer un tableau d'int pour la carte convertie
    int **int_map = (int **)malloc(map_height * sizeof(int *));
    for (int i = 0; i < map_height; i++)
        int_map[i] = (int *)malloc(map_width * sizeof(int));
    ray = (t_ray *)malloc(sizeof(t_ray));
    if (!ray)
    {
        ft_printf("Error\nmalloc() failed\n", 2);
        exit(1);
    }
    init_ray(ray);
    parse_map(ray, char_map, int_map, map_width, map_height);
    ray->map = int_map;
    ray->mlx = mlx_init();
    ray->mlx_win = mlx_new_window(ray->mlx, ray->screen_width, ray->screen_height, "Cub3D");
    if (!ray->mlx_win)
    {
        ft_printf("Error\nmlx_new_window() failed\n", 2);
        exit(1);
    }
    mlx_hook(ray->mlx_win, 2, 1L << 0, key_hook, ray);
    ray->img = mlx_new_image(ray->mlx, ray->screen_width, ray->screen_height);

    while (1)
    {
        ray->old_time = ray->time;
        ray->time = getTicks();  // Utilisez une fonction similaire à `getTicks()` pour obtenir le temps actuel en millisecondes

        // Calculez le temps de la frame
        ray->frame_time = (ray->time - ray->old_time) / 1000.0;  // Convertir en secondes

        // Imprimez le FPS
        printf("FPS: %f\n", 1.0 / ray->frame_time);  // Affiche le FPS, vous pouvez utiliser une méthode d'affichage adaptée à votre projet

        // Calculer la vitesse de déplacement et de rotation en fonction du temps de la frame
        ray->move_speed = ray->frame_time * 5.0;  // Constante en squares/seconde
        ray->rot_speed = ray->frame_time * 3.0;   // Constante en radians/seconde
        int x = 0;
        while (x < ray->screen_width)
        {
            ray->camera_x = 2 * x / (double)ray->screen_width - 1;
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
            if(ray->side == 0)
                ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
            else
                ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
            
            ray->line_height = (int)(ray->screen_height / ray->perp_wall_dist);
            ray->draw_start = -ray->line_height / 2 + ray->screen_height / 2;
            if (ray->draw_start < 0)
                ray->draw_start = 0;
            ray->draw_end = ray->line_height / 2 + ray->screen_height / 2;
            if (ray->draw_end >= ray->screen_height)
                ray->draw_end = ray->screen_height - 1;
            
            int color = (ray->map[ray->map_x][ray->map_y] == 1) ? 0xFFFFFF : 0x000000;

            if (ray->side == 1)
                color = color / 2;

            int y = ray->draw_start;
            while (y <= ray->draw_end)
            {
                mlx_pixel_put(ray->mlx, ray->mlx_win, x, y, color);
                y++;
            }
            x++;
        }
        mlx_loop(ray->mlx);
    }
}
