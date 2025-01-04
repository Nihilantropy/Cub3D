#include "../../include/cub3D_bonus.h"

static int	key_press(int keycode, t_game *game);
static int	key_release(int keycode, t_game *game);

/**
 * @brief Sets up keyboard and window event handlers
 *
 * @param game Game structure containing MLX window data
 */
void	handle_key_events(t_game *game)
{
	mlx_hook(game->win_ptr, X_EVENT_KEY_PRESS, 1L << 0, key_press, game);
	mlx_hook(game->win_ptr, X_EVENT_KEY_RELEASE, 1L << 1, key_release, game);
	mlx_hook(game->win_ptr, DESTROY_WIN_CLIENT_MSG, 0, close_game, game);
}

/**
 * @brief Updates player movement or rotation based on key press.
 *
 * @param keycode The key pressed.
 * @param game The game instance.
 * @return Always returns 0.
 */
static int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_FORWARD)
		set_player_movement(game, M_FORWARD);
	else if (keycode == KEY_S || keycode == KEY_BACKWARD)
		set_player_movement(game, M_BACKWARD);
	if (keycode == KEY_A || keycode == KEY_LEFT)
		set_player_rot_angle(game, R_LEFT);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		set_player_rot_angle(game, R_RIGHT);
	return (0);
}

/**
 * @brief Handles key release actions, stopping movement or closing the game.
 *
 * @param keycode The key released.
 * @param game The game instance.
 * @return Always returns 0.
 */
static int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	if (keycode == KEY_W || keycode == KEY_FORWARD)
		set_player_movement(game, M_STILL);
	else if (keycode == KEY_S || keycode == KEY_BACKWARD)
		set_player_movement(game, M_STILL);
	if (keycode == KEY_A || keycode == KEY_LEFT)
		set_player_rot_angle(game, R_STILL);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		set_player_rot_angle(game, R_STILL);
	return (0);
}