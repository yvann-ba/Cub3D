/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:09:05 by lauger            #+#    #+#             */
/*   Updated: 2024/09/20 10:49:02 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char*	deblank(char *input)
{
	char	*output;
	int		i;
	int		j;
	
	output = ft_calloc(sizeof(char), ft_strlen(input) + 1);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			output[j] = input[i];
		else
			j--;
		i++;
		j++;
	}
	return (output);
}
