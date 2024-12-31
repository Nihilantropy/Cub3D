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
	elapsed_time = (tv.tv_sec - last_frame_time.tv_sec) * 1000 + 
					(tv.tv_usec - last_frame_time.tv_usec) / 1000;
	if (elapsed_time < FRAME_TIME_MS)
		return (0);
	last_frame_time = tv;
	if (game->minimap.changed)
		render_3d_view(game);
	game->minimap.changed = false;
	return (0);
}

static void init_frame_buffer(t_game *game, t_render_state *state)
{
    state->img_ptr = mlx_new_image(game->mlx_ptr, 
        game->display.width, game->display.height);
    state->img_data = (int *)mlx_get_data_addr(state->img_ptr,
        &state->bits_per_pixel, &state->line_length, &state->endian);
}

static void clear_frame_buffer(t_render_state *state, t_game *game)
{
    int total_pixels;
    int i;

    total_pixels = game->display.width * game->display.height;
    i = 0;
    while (i < total_pixels)
    {
        state->img_data[i] = BLACK;  // Clear to black
        i++;
    }
}

void render_3d_view(t_game *game)
{
    t_render_state state;

    init_frame_buffer(game, &state);
    clear_frame_buffer(&state, game);
    render_floor_ceiling(game, &state);
    render_walls(game, &state);
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, 
        state.img_ptr, 0, 0);
	mlx_destroy_image(game->mlx_ptr, state.img_ptr);
}
