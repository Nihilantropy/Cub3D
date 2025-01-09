/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:54:48 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 11:54:49 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static int	key_press(int keycode, t_game *game);
static int	key_release(int keycode, t_game *game);
static int	mouse_pressed(int mousecode, int x, int y, void *param);
static int	mouse_release(int mousecode, int x, int y, void *param);

/**
 * @brief Sets up keyboard and window event handlers and disables key repeat
 *
 * @param game Game structure containing MLX window data
 */
void	handle_key_events(t_game *game)
{
	mlx_hook(game->win_ptr, X_EVENT_KEY_PRESS, 1L << 0, key_press, game);
	mlx_hook(game->win_ptr, X_EVENT_KEY_RELEASE, 1L << 1, key_release, game);
	mlx_hook(game->win_ptr, X_MOUSE_PRESS, 1L << 2, mouse_pressed, game);
	mlx_hook(game->win_ptr, X_MOUSE_RELEASE, 1L << 3, mouse_release, game);
	mlx_hook(game->win_ptr, DESTROY_WIN_CLIENT_MSG, 0, close_game, game);
}

/**
 * @brief Updates key state flags based on key press
 *
 * @param keycode Key that was pressed
 * @param game Game structure containing key states
 * @return Always returns 0
 */
static int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_FORWARD)
		game->keys.w_pressed = true;
	else if (keycode == KEY_S || keycode == KEY_BACKWARD)
		game->keys.s_pressed = true;
	else if (keycode == KEY_A)
		game->keys.a_pressed = true;
	else if (keycode == KEY_D)
		game->keys.d_pressed = true;
	else if (keycode == KEY_LEFT)
		game->keys.left_pressed = true;
	else if (keycode == KEY_RIGHT)
		game->keys.right_pressed = true;
	else if (keycode == KEY_SPACE)
		game->keys.space_pressed = true;
	return (0);
}

/**
 * @brief Updates key state flags based on key release
 *
 * @param keycode Key that was released
 * @param game Game structure containing key states
 * @return Always returns 0
 */
static int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	if (keycode == KEY_W || keycode == KEY_FORWARD)
		game->keys.w_pressed = false;
	else if (keycode == KEY_S || keycode == KEY_BACKWARD)
		game->keys.s_pressed = false;
	else if (keycode == KEY_A)
		game->keys.a_pressed = false;
	else if (keycode == KEY_D)
		game->keys.d_pressed = false;
	else if (keycode == KEY_LEFT)
		game->keys.left_pressed = false;
	else if (keycode == KEY_RIGHT)
		game->keys.right_pressed = false;
	else if (keycode == KEY_SPACE)
		game->keys.space_pressed = false;
	return (0);
}

/**
 * @brief Updates mouse button state flags
 *
 * @param mousecode Button that was pressed
 * @param x Mouse x position (unused)
 * @param y Mouse y position (unused)
 * @param param Game structure cast from void pointer
 * @return Always returns 0
 */
static int	mouse_pressed(int mousecode, int x, int y, void *param)
{
	t_game	*game;

	game = param;
	(void)x;
	(void)y;
	if (mousecode == MOUSE_LEFT)
		game->mouse.left = true;
	else if (mousecode == MOUSE_RIGHT)
		game->mouse.right = true;
	return (0);
}

static int	mouse_release(int mousecode, int x, int y, void *param)
{
	t_game	*game;

	game = param;
	(void)x;
	(void)y;
	if (mousecode == MOUSE_LEFT)
		game->mouse.left = false;
	else if (mousecode == MOUSE_RIGHT)
		game->mouse.right = false;
	return (0);
}
