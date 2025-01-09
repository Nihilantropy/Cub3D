/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:28:13 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 11:28:14 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_BONUS_H
# define OBJECT_BONUS_H

# include "cub3D_bonus.h"

/**
 * @brief object struct to keep track
 * of every object in the game
 */
typedef enum e_obj
{
	e_wall,
	e_door
}	t_obj;

#endif
