#include "../../include/cub3D_bonus.h"

static int	key_press(int keycode, t_game *game);
static int	key_release(int keycode, t_game *game);
static int	mouse_pressed(int mousecode, int x, int y, void *param);

/**
 * @brief Sets up keyboard and window event handlers
 *
 * @param game Game structure containing MLX window data
 */
void	handle_key_events(t_game *game)
{
	mlx_hook(game->win_ptr, X_EVENT_KEY_PRESS, 1L << 0, key_press, game);
	mlx_hook(game->win_ptr, X_EVENT_KEY_RELEASE, 1L << 1, key_release, game);
	mlx_hook(game->win_ptr, X_BUTTON_PRESS, 1L<<2, mouse_pressed, game);
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
		set_player_movement(game, m_forward);
	else if (keycode == KEY_S || keycode == KEY_BACKWARD)
		set_player_movement(game, m_backward);
	if (keycode == KEY_A)
		set_player_movement(game, m_left);
	else if (keycode == KEY_D)
		set_player_movement(game, m_right);
	else if (keycode == KEY_LEFT)
		set_player_rot_angle(game, r_left);
	else if (keycode == KEY_RIGHT)
		set_player_rot_angle(game, r_right);
	else if (keycode == KEY_SPACE)
		handle_door_interaction(game);
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
	if (keycode == KEY_W || keycode == KEY_FORWARD
		|| keycode == KEY_S || keycode == KEY_BACKWARD
		|| keycode == KEY_A || keycode == KEY_D)
		set_player_movement(game, m_still);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		set_player_rot_angle(game, r_still);
	return (0);
}

static int	mouse_pressed(int mousecode, int x, int y, void *param)
{
	t_game	*game;

	game = param;
	(void)x;
	(void)y;
	if (mousecode == MOUSE_LEFT)
		set_player_rot_angle(game, r_left);
	else if (mousecode == MOUSE_RIGHT)
		set_player_rot_angle(game, r_right);
	return (0);
}
