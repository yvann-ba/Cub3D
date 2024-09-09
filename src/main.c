#include "cub3d.h"

int main(int ac, char **av)
{

    (void)ac;
    (void)av;
    t_ray *ray;
    int map_width = 6;
    int map_height = 5;

    char *char_map[] = {
        "111111",
        "10S001",
        "110011",
        "100001",
        "111111",
        NULL
    };

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
    ray->img = mlx_new_image(ray->mlx, ray->screen_width, ray->screen_height);
    ray->addr = (int *)mlx_get_data_addr(ray->img, &ray->bpp, &ray->line_length, &ray->endian);

    mlx_hook(ray->mlx_win, 2, 1L << 0, key_hook, ray);

    mlx_loop_hook(ray->mlx, render_next_frame, ray); // Hook pour redessiner chaque frame
    mlx_loop(ray->mlx);  // Boucle principal

    return (0);
}

int render_next_frame(t_ray *ray)
{
    int x = 0;

    // Réinitialiser l'image avant chaque frame
    mlx_clear_window(ray->mlx, ray->mlx_win);

    // Raycasting logic pour chaque colonne d'écran
    while (x < ray->screen_width)
    {
        ray->camera_x = 2 * x / (double)ray->screen_width - 1;
        ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
        ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
        ray->map_x = (int)ray->pos_x;
        ray->map_y = (int)ray->pos_y;

        // Réinitialiser hit pour chaque rayon
        ray->hit = 0;

        // Calculer delta_dist (pour la distance entre les intersections)
        ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1 / ray->ray_dir_x);
        ray->delta_dist_y = (ray->ray_dir_y == 0) ? 1e30 : fabs(1 / ray->ray_dir_y);

        // Calcul des distances initiales (side_dist) et de la direction (step)
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

        // Algorithme DDA pour trouver où le rayon frappe un mur
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
            // Si le rayon touche un mur
            if (ray->map[ray->map_x][ray->map_y] > 0)
                ray->hit = 1;
        }

        // Calcul de la distance projetée du mur sur le plan de la caméra
        if (ray->side == 0)
            ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
        else
            ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;

        // Calcul de la hauteur de la ligne à dessiner sur l'écran
        ray->line_height = (int)(ray->screen_height / ray->perp_wall_dist);

        // Calcul des points de départ et fin pour dessiner la ligne
        ray->draw_start = -ray->line_height / 2 + ray->screen_height / 2;
        if (ray->draw_start < 0)
            ray->draw_start = 0;
        ray->draw_end = ray->line_height / 2 + ray->screen_height / 2;
        if (ray->draw_end >= ray->screen_height)
            ray->draw_end = ray->screen_height - 1;

        // Choix de la couleur (exemple simplifié : mur en blanc)
        int color = (ray->map[ray->map_x][ray->map_y] == 1) ? 0xFFFFFF : 0x000000;

        // Réduire la luminosité pour les murs côté Y
        if (ray->side == 1)
            color = color / 2;

        // Dessiner la ligne verticale (mur)
        for (int y = ray->draw_start; y < ray->draw_end; y++)
        {
            ray->addr[y * ray->line_length / 4 + x] = color;  // Écrire dans l'image mémoire
        }

        x++;
    }

    // Afficher l'image finale
    mlx_put_image_to_window(ray->mlx, ray->mlx_win, ray->img, 0, 0);

    // Gestion du temps (pour les FPS)
    ray->old_time = ray->time;
    ray->time = getTicks();
    ray->frame_time = (ray->time - ray->old_time) / 1000.0;

    // Éviter la division par zéro et afficher le FPS
    if (ray->frame_time > 0)
    {
        printf("FPS: %f\n", 1.0 / ray->frame_time);
    }

    // Calculer la vitesse de déplacement et de rotation en fonction du temps de la frame
    ray->move_speed = ray->frame_time * 5.0;  // Constante en squares/seconde
    ray->rot_speed = ray->frame_time * 3.0;   // Constante en radians/seconde

    return (0);
}
