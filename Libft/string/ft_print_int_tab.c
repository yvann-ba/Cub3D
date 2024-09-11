/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:24:47 by ybarbot           #+#    #+#             */
/*   Updated: 2024/09/11 10:54:39 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_print_int_tab(int **tab, int tab_height, int tab_width)
{
    int i;
    int j;

    i = 0;
    while (i < tab_height)
    {
        j = 0;
        while (j < tab_width)
        {
            ft_printf("%d", tab[i][j]);
            j++;      
        }
        ft_printf("\n");
        i++;
    }
}
