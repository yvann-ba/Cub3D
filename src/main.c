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
    read_file_to_string(data->fd_map, data);
    if (!data)
    {
        ft_printf("Error\nmalloc() failed\n", 2);
        exit(1);
    }
    free(data);
    return (0);
}
