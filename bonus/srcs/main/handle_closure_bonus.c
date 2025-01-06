#include "../../include/cub3D_bonus.h"

/**
 * @brief Handles the game closure process freeing allocated resources
 *
 * @param param Void pointer to game structure (cast to t_game internally)
 * @return int Returns 0 after successful cleanup and exit
 */
int	close_game(void *param)
{
	t_game	*game;

	game = param;
	free_all_and_exit(game, EXIT_SUCCESS);
	return (0);
}