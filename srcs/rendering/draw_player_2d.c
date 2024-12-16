#include "../include/cub3D.h"

/**
 * @brief draw the player on the 2D map based on their exact position.
 * This function ensures smooth rendering and is called at every player movement.
 */
void	draw_player_2d(t_game *game)
{
    double x_world;
    double y_world;
    int line_length = 1;  // Length of the line (adjust as needed)
    double line_end_x;
    double line_end_y;

    // Get player's world position
    x_world = game->player.pos.x;
    y_world = game->player.pos.y;

    // Calculate the position of the line endpoint based on the current angle
    line_end_x = x_world + cos(game->player.rot.current_angle) * line_length;
    line_end_y = y_world + sin(game->player.rot.current_angle) * line_length;

    // Convert player position to screen coordinates
    game->player.pos.x_screen = (int)(x_world * MINI_CELL_SIZE - MINI_PLAYER_SIZE / 2);
    game->player.pos.y_screen = (int)(y_world * MINI_CELL_SIZE - MINI_PLAYER_SIZE / 2);

    // Convert line endpoint to screen coordinates
    int line_end_x_screen = (int)(line_end_x * MINI_CELL_SIZE);
    int line_end_y_screen = (int)(line_end_y * MINI_CELL_SIZE);

    // Draw the player (yellow square)
    mlx_put_image_to_window(
        game->mlx_ptr,
        game->win_ptr,
        game->minimap.images.player,
        game->player.pos.x_screen - MINI_PLAYER_SIZE / 2,
        game->player.pos.y_screen - MINI_PLAYER_SIZE / 2
    );

    // Draw a small pixel line following the angle (you can use mlx_pixel_put for this)
   draw_line(game, game->player.pos.x_screen, game->player.pos.y_screen, line_end_x_screen, line_end_y_screen, RED);
}
