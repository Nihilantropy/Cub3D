#include "../include/cub3D.h"

/**
 * @brief clear and draw map and player each frame
 * 
 * This function clears the window and draws the map only when it changes,
 * and the player is redrawn when necessary.
 */
int	render_frame(t_game *game)
{
	struct timeval			tv;
	static struct timeval	last_frame_time;
	long					elapsed_time;

	if (last_frame_time.tv_sec == 0 && last_frame_time.tv_usec == 0)
	{
		last_frame_time.tv_sec = 0;
		last_frame_time.tv_usec = 0;
	}
	gettimeofday(&tv, NULL);
	elapsed_time = (tv.tv_sec - last_frame_time.tv_sec) * 1000 + \
					(tv.tv_sec - last_frame_time.tv_usec) / 1000;
	if (elapsed_time < FRAME_TIME_MS)
		return (0);
	last_frame_time = tv;
	if (game->minimap.changed)
	{
		mlx_clear_window(game->mlx_ptr, game->win_ptr);
		draw_map_2d(game);
		draw_player_2d(game);
		cast_ray(game, &game->player);
	}
	game->minimap.changed = false;
	return (0);
}
