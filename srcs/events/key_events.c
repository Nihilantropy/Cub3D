#include "../include/cub3D.h"

static int	key_press(int keycode, t_game *game);
static int	key_release(int keycode, t_game *game);

/**
 * @brief main function to handle key events
*/
void	handle_events(t_game *game)
{
	mlx_hook(game->win_ptr, X_EVENT_KEY_PRESS, 1L << 0, key_press, game);
	mlx_hook(game->win_ptr, X_EVENT_KEY_RELEASE, 1L << 1, key_release, game);
	mlx_hook(game->win_ptr, DESTROY_WIN_CLIENT_MSG, 0, close_game, game);
}

static int	key_press(int keycode, t_game *game)
{
	printf("Pressed: %d\n", keycode);

	(void)keycode;
	(void)game;
	// if (keycode == KEY_W || keycode == KEY_FORWARD)
	// 	game->move.x = 1;
	// else if (keycode == KEY_S || keycode == KEY_BACKWARD)
	// 	game->move.y = 1;
	// if (keycode == KEY_A)
	// 	game->x_move.x = 1;
	// else if (keycode == KEY_D)
	// 	game->x_move.y = 1;
	// if (keycode == KEY_Q || keycode == KEY_LEFT)
	// 	game->rotate.x = 1;
	// else if (keycode == KEY_E || keycode == KEY_RIGHT)
	// 	game->rotate.y = 1;
	return (0);
}

static int	key_release(int keycode, t_game *game)
{
	printf("Release: %d\n", keycode);
	if (keycode == KEY_ESC)
		close_game(game);
	// if (keycode == KEY_W || keycode == KEY_FORWARD)
	// 	game->move.x = 0;
	// else if (keycode == KEY_S || keycode == KEY_BACKWARD)
	// 	game->move.y = 0;
	// else if (keycode == KEY_A)
	// 	game->x_move.x = 0;
	// else if (keycode == KEY_D)
	// 	game->x_move.y = 0;
	// else if (keycode == KEY_Q || keycode == KEY_LEFT)
	// 	game->rotate.x = 0;
	// else if (keycode == KEY_E || keycode == KEY_RIGHT)
	// 	game->rotate.y = 0;
	return (0);
}