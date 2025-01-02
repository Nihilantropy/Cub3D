#include "../include/cub3D.h"

static void render_3d_view(t_game *game);
static void init_frame_buffer(t_game *game, t_render_state *state);
static void clear_frame_buffer(t_render_state *state, t_game *game);

/**
 * @brief Renders a new frame if enough time has passed since the last frame.
 * 
 * This function checks the time elapsed since the last frame and, if sufficient time has passed,
 * triggers the rendering of a new 3D view.
 * @param game The game state that holds the necessary data for rendering.
 * @return Always returns 0.
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
	if (game->changed)
		render_3d_view(game);
	game->changed = false;
	return (0);
}

/**
 * @brief Renders the 3D view of the game, including the floor, ceiling, and walls.
 * 
 * This function initializes and clears the frame buffer, renders the floor and ceiling, 
 * then iterates over each column of the screen to render the walls. Finally, it displays the image.
 * @param game The game state used to access rendering and display parameters.
 * @param state The render state used to store the image data during the rendering process.
 */
static void render_3d_view(t_game *game)
{
	t_render_state	state;
	int				x;

	init_frame_buffer(game, &state);
	clear_frame_buffer(&state, game);
	render_floor_ceiling(game, &state);
	x = 0;
	while (x < game->display.width)
	{
		render_walls(game, &state, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, 
		state.img_ptr, 0, 0);
	mlx_destroy_image(game->mlx_ptr, state.img_ptr);
}

/**
 * @brief Initializes the frame buffer for rendering.
 * 
 * This function creates a new image and sets up the necessary data pointer for the frame buffer.
 * @param game The game state that provides access to the display dimensions and mlx pointer.
 * @param state The render state where the image pointer and data are stored.
 */
static void init_frame_buffer(t_game *game, t_render_state *state)
{
	state->img_ptr = mlx_new_image(game->mlx_ptr, 
		game->display.width, game->display.height);
	state->img_data = (int *)mlx_get_data_addr(state->img_ptr,
		&state->bits_per_pixel, &state->line_length, &state->endian);
}

/**
 * @brief Clears the frame buffer by setting all pixels to black.
 * 
 * This function iterates through all pixels in the frame buffer and sets their color to black.
 * @param state The render state containing the image data to be cleared.
 * @param game The game state used to access display dimensions.
 */
static void clear_frame_buffer(t_render_state *state, t_game *game)
{
	int total_pixels;
	int i;

	total_pixels = game->display.width * game->display.height;
	i = 0;
	while (i < total_pixels)
	{
		state->img_data[i] = BLACK;
		i++;
	}
}
