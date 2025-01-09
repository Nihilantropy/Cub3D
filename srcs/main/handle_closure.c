/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_closure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:54:54 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 10:54:55 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
