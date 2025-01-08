#include "../../include/cub3D_bonus.h"

static void	update_movement(t_game *game);
static void	update_rotation(t_game *game);

void	handle_key_update(t_game *game)
{
	update_movement(game);
	update_rotation(game);
	if (game->keys.space_pressed)
	{
		handle_door_interaction(game);
		game->keys.space_pressed = false;
	}
}

/**
 * @brief Updates player movement based on current key states
 *
 * @param game Game structure containing movement states
 */
static void	update_movement(t_game *game)
{
	if (game->keys.w_pressed)
		set_player_movement(game, m_forward);
	else if (game->keys.s_pressed)
		set_player_movement(game, m_backward);
	if (game->keys.a_pressed)
		set_player_movement(game, m_left);
	else if (game->keys.d_pressed)
		set_player_movement(game, m_right);
	if (!game->keys.w_pressed && !game->keys.s_pressed
		&& !game->keys.a_pressed && !game->keys.d_pressed)
		set_player_movement(game, m_still);
}

static void	update_rotation(t_game *game)
{
	if (game->keys.left_pressed)
		set_player_rot_angle(game, r_left);
	else if (game->keys.right_pressed)
		set_player_rot_angle(game, r_right);
	if (game->mouse.left)
		set_player_rot_angle(game, r_left);
	else if (game->mouse.right)
		set_player_rot_angle(game, r_right);
	if (!game->keys.left_pressed && !game->keys.right_pressed
		&& !game->mouse.left && !game->mouse.right)
		set_player_rot_angle(game, r_still);
}