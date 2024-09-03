#include "cub3d.h"

//int main(int ac, char **av)
int main(int ac, char **av)
{
    t_data *data;

    if (ac != 2)
    {
        ft_printf(RED"Error:\nNumber of arguments is incorrect:" WHITE"require format (./cub3d file.cub)");
        return (1);
    }
    data = malloc(sizeof(t_data));
    data->fd_map = open_file(av[1], data);
    if (!data)
    {
        ft_printf("Error\nmalloc() failed\n", 2);
        exit(1);
    }
    data->mlx = mlx_init();
    data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
    if (!data->mlx_win)
    {
        ft_printf("Error\nmlx_new_window() failed\n", 2);
        exit(1);
    }
    data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
    data->addr = (int *)mlx_get_data_addr(data->img, &data->bpp, &data->line_length, data->addr);
    mlx_loop(data->mlx);
}
