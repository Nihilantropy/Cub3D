/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_closure_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:57:02 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 11:57:03 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

/**
 * @brief Handles the game closure process freeing allocated resources
 *
 * @param param Void pointer to game structure (cast to t_game internally)
 * @return int Returns 0 after successful cleanup and exit
 */
int	close_game(void *param)
{
	t_game	*game;

	game = param;
	free_all_and_exit(game, EXIT_SUCCESS);
	return (0);
}
