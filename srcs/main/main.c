/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:54:57 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 10:56:23 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * @brief Main entry point for the Cub3D game. Initializes game structures,
 * validates input, sets up display, and starts the game loop.
 *
 * @param argc Number of command-line arguments
 * @param argv Array of command-line arguments,
 * where argv[1] is the map file path
 * @return int Returns 0 on successful execution,
 * exits with failure status on errors
 */
int	main(int argc, char **argv)
{
	t_game	game;

	if (check_valid_arg(argc, argv) == false)
	{
		ft_putstr_fd(ERR_ARG, 2);
		ft_putstr_fd(P_USAGE, 2);
		exit (EXIT_FAILURE);
	}
	init_game(&game);
	if (get_map(&game, argv[1]) == false)
		free_all_and_exit(&game, EXIT_FAILURE);
	game.mlx_ptr = mlx_init();
	if (!handle_display(&game))
		free_all_and_exit(&game, EXIT_FAILURE);
	game.running = true;
	game_loop(&game);
	game.running = false;
	free_all_and_exit(&game, EXIT_SUCCESS);
	return (0);
}

/**
 * @brief Manages the main game loop, handling keyboard events and
 * rendering frames continuously while the game is running
 *
 * @param game Pointer to the game structure containing MLX and game state data
 */
void	game_loop(t_game *game)
{
	if (game->running)
	{
		handle_key_events(game);
		mlx_loop_hook(game->mlx_ptr, render_frame, game);
		mlx_loop(game->mlx_ptr);
	}
}
