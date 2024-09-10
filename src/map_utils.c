#include "cub3d.h"

int **allocate_int_map(t_data *data)
{
    int **int_map;
    int i;

	data->map_width = (int)ft_strlen(data->map[0]);
	data->map_height = ft_tab_len(data->map);
    int_map = (int **)malloc(data->map_height * sizeof(int *));
    if (!int_map)
    {
        ft_printf("Error\nmalloc() failed\n", 2);
        exit(1);
    }
    i = 0;
    while (i < data->map_height)
    {
        int_map[i] = (int *)malloc(data->map_width * sizeof(int));
        if (!int_map[i])
        {
            ft_printf("Error\nmalloc() failed\n", 2);
            exit(1);
        }
        i++;
    }
    return (int_map);
}

void set_player_position(t_ray *ray, int x, int y, char direction)
{
    ray->pos_x = x + 0.5;
    ray->pos_y = y + 0.5;
    if (direction == 'N')
    {
        ray->dir_x = 0;
        ray->dir_y = -1;
        ray->plane_x = 0.66;
        ray->plane_y = 0;
    }
    else if (direction == 'S')
    {
        ray->dir_x = 0;
        ray->dir_y = 1;
        ray->plane_x = -0.66;
        ray->plane_y = 0;
    }
    else if (direction == 'E')
    {
        ray->dir_x = 1;
        ray->dir_y = 0;
        ray->plane_x = 0;
        ray->plane_y = 0.66;
    }
    else if (direction == 'W')
    {
        ray->dir_x = -1;
        ray->dir_y = 0;
        ray->plane_x = 0;
        ray->plane_y = -0.66;
    }
}

void parse_map(t_ray *ray, t_data *data, int **int_map)
{
    int y;
    int x;

    y = 0;
    while (y < data->map_height)
    {
        x = 0;
        while (x < data->map_width)
        {
            if (data->map[y][x] == '1')
                int_map[y][x] = 1;
            else if (data->map[y][x] == '0')
                int_map[y][x] = 0;
            else if (data->map[y][x] == 'N' || data->map[y][x] == 'S' \
            || data->map[y][x] == 'E' || data->map[y][x] == 'W')
            {
                set_player_position(ray, x, y, data->map[y][x]);
                int_map[y][x] = 0;
            }
            x++;
        }
        y++;
    }
}
