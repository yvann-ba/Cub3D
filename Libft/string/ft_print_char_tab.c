/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:24:47 by ybarbot           #+#    #+#             */
/*   Updated: 2024/09/11 10:33:45 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_print_char_tab(char **tab)
{
    int i;
    int tab_len;

    i = 0;
    tab_len = ft_tab_len(tab);
    while (i < tab_len)
    {
        ft_printf("%s\n", tab[i]);
        i++;
    }
}
