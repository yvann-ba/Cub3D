/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:42:14 by lauger            #+#    #+#             */
/*   Updated: 2024/09/24 13:26:22 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	string_to_tab(t_read_file *rf)
{
	if (!rf || !rf->str_content)
		return ;
	rf->tab_content = NULL;
	rf->tab_content = ft_split((const char *)rf->str_content, '\n');
	if (rf->tab_content == NULL)
	{
		ft_putstr_fd(RED "Error:\nInvalid malloc:"
			WHITE" each part must be separated with '\\n'\n", 2);
		pars_clean_exit(rf->data);
	}
	free(rf->str_content);
	rf->str_content = NULL;
	return ;
}
