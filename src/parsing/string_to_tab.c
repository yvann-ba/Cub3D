/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:08:25 by lauger            #+#    #+#             */
/*   Updated: 2024/09/04 11:21:27 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// This is tempory function
void print_2d_array(char **array, int rows) {
    for (int i = 0; i < rows; i++) {
        printf("%s\n", array[i]);
    }
}

void string_to_tab(t_read_file *rf)
{
    if (!rf || !rf->str_content)
        return;

    rf->tab_content = NULL;
    rf->tab_content = ft_split((const char *)rf->str_content, '\n');
    if (rf->tab_content == NULL)
    {
        perror(RED "Error:\nInvalid malloc" WHITE);
        free(rf->str_content);
        free(rf->data);
        free(rf);
        exit(1);
    }
    free(rf->str_content);
    print_2d_array(rf->tab_content, 21);
    return ;
}