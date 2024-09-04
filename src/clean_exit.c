/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:30:12 by lauger            #+#    #+#             */
/*   Updated: 2024/09/04 09:38:31 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    clean_exit(t_data *data)
{
    if (data->read_file.str_content == NULL)
        free(data->read_file.str_content);
    if (data->read_file.tab_content)
        ft_free_tab(data->read_file.tab_content);
    if (data)
        free(data);
    exit(0);
}