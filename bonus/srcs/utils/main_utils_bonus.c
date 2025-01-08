#include "../../include/cub3D_bonus.h"

void	free_all_and_exit(t_game *game, int status)
{
	if (game)
	{
		if (game->mlx_ptr && game->win_ptr)
			mlx_mouse_show(game->mlx_ptr, game->win_ptr);
		if (game->win_ptr && game->mlx_ptr)
			mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		free_matrix((char **)game->map.matrix);
		free_bool_matrix(game->map.check.visited);
		free_info_list(&game->map.check.info);
		free_textures(game);
		free_door_system(game);
		if (game->mlx_ptr)
		{
			mlx_destroy_display(game->mlx_ptr);
			free(game->mlx_ptr);
		}
		free(game);
	}
	exit(status);
}
