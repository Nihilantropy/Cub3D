#include "../include/cub3D.h"

static void fill_horizontal_line(t_render_state *state, int y, 
                               int width, int color)
{
    int x;

    x = 0;
    while (x < width)
    {
        state->img_data[y * width + x] = color;
        x++;
    }
}

void render_floor_ceiling(t_game *game, t_render_state *state)
{
    int y;
    int half_height;

    half_height = game->display.height / 2;
    
    // Render ceiling (top half)
    y = 0;
    while (y < half_height)
    {
        fill_horizontal_line(state, y, game->display.width, 
                           game->textures.ceiling_color);
        y++;
    }

    // Render floor (bottom half)
    while (y < game->display.height)
    {
        fill_horizontal_line(state, y, game->display.width, 
                           game->textures.floor_color);
        y++;
    }
}