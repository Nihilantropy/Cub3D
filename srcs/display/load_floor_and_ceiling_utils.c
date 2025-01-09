/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_floor_and_ceiling_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:50:56 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 10:50:57 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * @brief Validates RGB color values are within valid range (0-255)
 *
 * @param rgb Array of 3 RGB color values as strings
 * @return bool true if values valid, false otherwise
 */
bool	check_rgb_values(const char **rgb)
{
	int	value;
	int	i;

	if (!rgb || matrix_len(rgb) != 3)
		return (false);
	i = 0;
	while (rgb[i])
	{
		value = ft_atoi(rgb[i]);
		if (value < 0 || value > 255)
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Creates RGB color value from array of color components
 *
 * @param rgb Array of RGB values as strings
 * @return int Combined RGB value as single integer
 */
int	create_rgb(const char **rgb)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	return ((r << 16) | (g << 8) | b);
}
