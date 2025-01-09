/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_player_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:00:14 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 12:01:03 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static void	set_player_var(t_game *game, int y, int x);
static void	set_player_pos(t_game *game, int y, int x);
static void	set_player_rot(t_game *game, char face);

/**
 * @brief Finds and sets the player's position in the map.
 *
 * Scans the map matrix for the player character, updates the player's position,
 * and marks the position as FLOOR.
 * @param game The game object containing the map.
 * @return None.
 */
void	get_player_infos(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map.matrix[y])
	{
		x = 0;
		while (game->map.matrix[y][x])
		{
			if (is_player_char(game->map.matrix[y][x]))
			{
				game->map.check.player++;
				set_player_var(game, y, x);
				game->map.matrix[y][x] = FLOOR;
				return ;
			}
			x++;
		}
		y++;
	}
}

bool	is_player_char(char player)
{
	return (player == NORTH || player == EAST
		|| player == SOUTH || player == WEST);
}

/**
 * @brief Initializes player variables based on the player's position.
 *
 * Sets the player's facing direction, speed,
 * rotation speed, position, and rotation
 * according to the given coordinates on the map.
 * @param game The game object containing the player and map data.
 * @param y The row index of the player's position in the map.
 * @param x The column index of the player's position in the map.
 * @return None.
 */
static void	set_player_var(t_game *game, int y, int x)
{
	game->player.face = game->map.matrix[y][x];
	game->player.speed = P_SPEED;
	game->player.rot_speed = R_SPEED;
	set_player_pos(game, y, x);
	set_player_rot(game, game->player.face);
}

/**
 * @brief Sets the player's position with an offset.
 *
 * @param game The game object.
 * @param y The row index.
 * @param x The column index.
 * @return None.
 */
static void	set_player_pos(t_game *game, int y, int x)
{
	game->player.pos.y = y + 0.5;
	game->player.pos.x = x + 0.5;
}

/**
 * @brief Sets the player's camera direction and
 * plane based on the facing direction.
 *
 * @param game The game object.
 * @param face The player's facing direction (NORTH, EAST, SOUTH, WEST).
 * @return None.
 */
static void	set_player_rot(t_game *game, char face)
{
	if (face == NORTH)
		set_north_rot(game);
	else if (face == EAST)
		set_east_rot(game);
	else if (face == SOUTH)
		set_south_rot(game);
	else if (face == WEST)
		set_west_rot(game);
}
