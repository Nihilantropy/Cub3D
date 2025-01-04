#include "../../include/cub3D_bonus.h"

/**
 * @brief Attempts to slide player along walls when direct movement is blocked.
 *
 * Checks horizontal and vertical movement separately to allow sliding
 * when one direction is blocked. Updates position only if movement is possible.
 *
 * @param game Pointer to game structure
 * @param new_pos Pointer to store new position
 * @param step_x X-axis movement step
 * @param step_y Y-axis movement step
 * @return true if sliding movement was possible, false otherwise
 */
bool try_slide_movement(t_game *game, t_pos *new_pos, 
							double step_x, double step_y)
{
	bool moved;
	t_pos temp_pos;

	moved = false;
	temp_pos = *new_pos;
	if (is_valid_pos((const char **)game->map.matrix, 
		game->player.pos.y, game->player.pos.x + step_x))
	{
		temp_pos.x = game->player.pos.x + step_x;
		temp_pos.y = game->player.pos.y;
		moved = true;
	}
	if (is_valid_pos((const char **)game->map.matrix, 
		game->player.pos.y + step_y, game->player.pos.x))
	{
		temp_pos.y = game->player.pos.y + step_y;
		temp_pos.x = game->player.pos.x;
		moved = true;
	}
	if (moved)
		*new_pos = temp_pos;
	return (moved);
}
