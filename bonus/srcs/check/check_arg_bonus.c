/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:38:07 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 11:38:08 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static bool	check_extention(char *str);

/**
 * @brief Validates command line arguments and map file extension
 *
 * @param argc Arguments count
 * @param argv Arguments array
 * @return bool true if valid, false otherwise
 */
bool	check_valid_arg(int argc, char **argv)
{
	if (argc != 2)
		return (false);
	else if (check_extention(argv[1]) == false)
		return (false);
	return (true);
}

/**
 * @brief Checks if file has .cub extension
 *
 * @param str File path to check
 * @return bool true if extension is valid, false otherwise
 */
static bool	check_extention(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (i < 4)
		return (1);
	if (str[i] == 'b' && str[i - 1] == 'u' && str[i - 2] == 'c'
		&& str[i - 3] == '.')
		return (true);
	else
		return (false);
}
