/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:27:09 by lauger            #+#    #+#             */
/*   Updated: 2024/09/19 13:04:24 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	append_char(char *str, char ch)
{
	int	len;

	len = ft_strlen(str);
	str[len] = ch;
	str[len + 1] = '\0';
}

char	*int_to_hex(int	n)
{
	char	tmp;
	int		rem; // remainder variable to store remainder
	char	ch; // ch variable to store each character
	char	*res;
	int		i;
	int		j;
  
	res = ft_calloc(3,sizeof(char));
	rem = 0;
	i = 0;
	while (n != 0)
	{
		// storing remainder in rem variable.
		rem = n % 16;
		// check if temp < 10
		if (rem < 10)
			ch = rem + 48;
		else
			ch = rem + 55;
		// updating the res string with the character variable
		append_char(res, ch);
		n = n / 16;
	}
	printf(RED"value--> %s\n"WHITE, res);
	j = ft_strlen(res) - 1;
	while(i <= j)
	{
		tmp = res[i];
		res[i] = res[j];
		res[j] = tmp;
		i++;
		j--;
	}
	return (res);
}

char	*convert_rgb_to_hex(int R, int G, int B)
{
	char	*hex_code;
	char	*red;
	char	*green;
	char	*blue;

	if ((R >= 0 && R <= 255)
		&& (G >= 0 && G <= 255)
		&& (B >= 0 && B <= 255))
	{
		red = int_to_hex(R);
		green = int_to_hex(G);
		blue = int_to_hex(B);
		hex_code = ft_calloc(17,1);
		//append_char(hex_code, '#');
		ft_strcat(hex_code, red);
		ft_strcat(hex_code, green);
		ft_strcat(hex_code, blue);
		free(red);
		free(green);
		free(blue);
		return (hex_code);
	}
	else
		return (NULL);
}
