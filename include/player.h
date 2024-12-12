#ifndef PLAYER_H
# define PLAYER_H

#include <stdbool.h>

/**
 * @brief Stores the player's position on the map.
 * 
 * @var x X-coordinate of the player.
 * @var y Y-coordinate of the player.
 */
typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

/**
 * @brief Stores the player's angle and rotation direction.
 * 
 * @var current_angle Current angle of the player.
 * @var next_angle True for positive rotation, false for negative.
 */
typedef struct s_rot
{
	double	current_angle;
	bool	next_angle;
}	t_rot;

/**
 * @brief Stores player information, including direction, position, and rotation.
 * 
 * @var face Initial direction ('N', 'W', 'E', or 'S').
 * @var pos Player's position on the map.
 * @var rot Player's rotation details.
 */
typedef struct s_player
{
	char	face;
	t_pos	pos;
	t_rot	rot;
}	t_player;

#endif