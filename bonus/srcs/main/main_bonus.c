#include "../../include/cub3D_bonus.h"

/**
 * @brief Main entry point for the Cub3D game. Initializes game structures,
 * validates input, sets up display, and starts the game loop.
 *
 * @param argc Number of command-line arguments
 * @param argv Array of command-line arguments, where argv[1] is the map file path
 * @return int Returns 0 on successful execution, exits with failure status on errors
 */
int	main(int argc, char **argv)
{
	t_game	*game;

	game = NULL;
	if (check_valid_arg(argc, argv) == false)
	{
		ft_putstr_fd(ERR_ARG, 2);
		ft_putstr_fd(P_USAGE, 2);
		exit(EXIT_FAILURE);
	}
	game = init_game();
	if (get_map(game, argv[1]) == false)
		free_all_and_exit(game, EXIT_FAILURE);
	game->mlx_ptr = mlx_init();
	if (!handle_display(game))
		free_all_and_exit(game, EXIT_FAILURE);
	game->running = true;
	handle_key_events(game);
	mlx_loop_hook(game->mlx_ptr, game_loop, game);
	mlx_loop(game->mlx_ptr);
	game->running = false;
	free_all_and_exit(game, EXIT_SUCCESS);
	return (0);
}

/**
 * @brief Manages the main game loop, handling keyboard events and
 * rendering frames continuously while the game is running
 *
 * @param game Pointer to the game structure containing MLX and game state data
 */
int	game_loop(t_game *game)
{
	struct timeval			tv;
	static struct timeval	last_frame_time;
	long					elapsed_time;

	gettimeofday(&tv, NULL);
	elapsed_time = (tv.tv_sec - last_frame_time.tv_sec) * 1000 +
			(tv.tv_usec - last_frame_time.tv_usec) / 2000;
	if (elapsed_time < FRAME_TIME_MS)
		return (0);
	handle_key_update(game);
	handle_mouse_update(game);
	render_frame(game);
	last_frame_time = tv;
	return (0);
}
