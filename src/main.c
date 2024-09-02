#include "../includes/cub3d.h"

//int main(int ac, char **av)
int main(void)
{
    void *mlx;
    void *mlx_win;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
    mlx_loop(mlx);
}
