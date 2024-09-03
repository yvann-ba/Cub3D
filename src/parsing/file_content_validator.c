/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content_validator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:50:40 by lauger            #+#    #+#             */
/*   Updated: 2024/09/03 14:15:48 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void    add_eof_content(t_read_file *rf)
{
    if (rf->bytes_read < 0) {
        perror("read");
        free(rf->content);
        clean_exit(rf->data);
    }
    if (rf->content != NULL) {
        rf->content[rf->total_size] = '\0';
    } else {
        rf->content = malloc(1);
        if (rf->content == NULL) {
            perror("malloc");
            clean_exit(rf->data);
        }
        rf->content[0] = '\0';
    }
}

static t_read_file init_rf(t_data *data, int fd)
{
    t_read_file rf;
    
    rf.content = NULL;
    rf.total_size = 0;
    rf.data = data;
    if (fd < 0)
    {
        perror("Invalid file descriptor");
        clean_exit(rf.data);
    }
    return (rf);
}

char *read_file_to_string(int fd, t_data *data)
{
    t_read_file rf;

    rf = init_rf(data, fd);
    while ((rf.bytes_read = read(fd, rf.buffer, sizeof(rf.buffer))) > 0)
    {
        rf.new_size = rf.total_size + rf.bytes_read;
        char *new_content = ft_realloc(rf.content, rf.new_size + 1, ft_strlen(rf.content));
        if (new_content == NULL) {
            perror("realloc");
            free(rf.content);
           clean_exit(rf.data);
        }

        rf.content = new_content;
        ft_memcpy(rf.content + rf.total_size, rf.buffer, rf.bytes_read);
        rf.total_size += rf.bytes_read;
    }
    add_return_content(&rf);
    ft_printf("FILE_CONTENT: %s\n", rf.content);
    return (rf.content);
}