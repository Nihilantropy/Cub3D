#include "../include/cub3D.h"

/** 
 * @brief main:
 *	1) check for incorrect arguments
 *	2) initialize the game structure
 *	3) get the map to parse and validate
 *		the map infos and the map matrix
 */
int	main(int argc, char **argv)
{
	t_game	game;

	if (check_valid_arg(argc, argv) == false)
	{
		ft_putstr_fd(ERR_ARG, 2);
		ft_putstr_fd(P_USAGE, 2);
		return (1);
	}
	init_game(&game);
	if (get_map(&game, argv[1]) == false)
	{
		free_all(&game);
		return (1);
	}
	game.mlx_ptr = mlx_init();
	handle_display(&game);
	game.running = true;
	game_loop(&game);
	game.running = false;
	free_all(&game);
	return (0);
}

void	game_loop(t_game *game)
{
	if (game->running)
	{
		handle_key_events(game);
		mlx_loop_hook(game->mlx_ptr, render_frame, game);
		mlx_loop(game->mlx_ptr);
	}
}
