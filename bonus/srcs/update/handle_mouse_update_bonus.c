/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_update_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:54:04 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 13:56:45 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static bool	handle_mouse_x_edges(t_game *game);

/**
 * @brief Updates mouse position and handles rotation based on movement
 *
 * @param game Game structure containing mouse and display data
 */
void	handle_mouse_update(t_game *game)
{
	int	old_x;

	old_x = game->mouse.x;
	if (!mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr,
			&game->mouse.x, &game->mouse.y))
	{
		ft_putstr_fd(ERR_MOUSE_QUERY, 2);
		free_all_and_exit(game, EXIT_FAILURE);
	}
	handle_mouse_appear(game, game->mouse.x, game->mouse.y);
	if (game->mouse.show)
		return ;
	if (handle_mouse_x_edges(game))
		return ;
	if (old_x < game->mouse.x)
		set_player_rot_angle(game, r_right);
	else if (old_x > game->mouse.x)
		set_player_rot_angle(game, r_left);
	else
		set_player_rot_angle(game, r_still);
}

/**
 * @brief Handles mouse behavior at screen edges
 *
 * @param game Game structure containing display dimensions
 * @return true if mouse is at edge, false otherwise
 */
static bool	handle_mouse_x_edges(t_game *game)
{
	if (game->mouse.x == 0)
	{
		set_player_rot_angle(game, r_left);
		return (true);
	}
	else if (game->mouse.x == game->display.width -1)
	{
		set_player_rot_angle(game, r_right);
		return (true);
	}
	return (false);
}

/**
 * @brief Controls mouse cursor if in game window
 *
 * @param game Game structure containing mouse and display data
 * @param x Current mouse X position
 * @param y Current mouse Y position
 */
void	handle_mouse_appear(t_game *game, int x, int y)
{
	if ((x < 0 || x > game->display.width)
		|| (y < 0 || y > game->display.height))
	{
		if (!game->mouse.show)
			game->mouse.show = true;
	}
	else if (game->mouse.show)
		game->mouse.show = false;
}
