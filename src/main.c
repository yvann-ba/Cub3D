#include "cub3d.h"

//int main(int ac, char **av)
int main(void)
{
    t_data *data;

    data = malloc(sizeof(t_data));
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
    data.addr = (int *)mlx_get_data_addr(data->img, &data->bpp, &data->line_length, &data->addr);
    mlx_loop(mlx);
}
