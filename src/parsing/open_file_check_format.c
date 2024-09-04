/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_check_format.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:37:56 by lauger            #+#    #+#             */
/*   Updated: 2024/09/04 08:59:52 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool    has_cub_extenssion(char *filename)
{
    size_t  len;

    if (!filename)
        return (false);
    len = ft_strlen(filename);
    if (len < 4)
        return (false);
    if (ft_strcmp(filename + len - 4, ".cub") == 0)
        return (true);
    return (false);
}

int    open_file(char *file, t_data *data)
{
    int     fd;
    
    if (!file || !data)
        return (-1);
    if (has_cub_extenssion(file) == false)
    {
        printf(RED"Error:\nFailed to open file:"
            WHITE" file must have .cub extenssion\n");
        clean_exit(data);
    }
    fd = open(file, O_RDONLY, 0);
    if (fd == -1)
    {
        printf(RED"Error:\nFailed to open file:"
            WHITE" %s\n", strerror(errno));
        clean_exit(data);
    }
    return (fd);
}