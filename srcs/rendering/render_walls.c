#include "../include/cub3D.h"

static void calculate_wall_slice(t_wall_slice *slice, t_game *game, 
    double perp_wall_dist)
{
    slice->height = (int)(game->display.height / perp_wall_dist);
    slice->start_y = -slice->height / 2 + game->display.height / 2;
    slice->end_y = slice->height / 2 + game->display.height / 2;
    
    if (slice->start_y < 0)
        slice->start_y = 0;
    if (slice->end_y >= game->display.height)
        slice->end_y = game->display.height - 1;
}

static void draw_wall_slice(t_render_state *state, t_wall_slice *slice,
    t_game *game, int x)
{
    int y;
    int color;

    y = slice->start_y;
    while (y < slice->end_y)
    {
        color = determine_wall_color(slice->side, slice->distance);
        state->img_data[y * game->display.width + x] = color;
        y++;
    }
}

void render_walls(t_game *game, t_render_state *state)
{
    int x;
    t_wall_slice slice;
    
    x = 0;
    while (x < game->display.width)
    {
        cast_ray(game, &game->player, x);
        calculate_wall_slice(&slice, game, 
            game->player.camera.perp_wall_dist);
        draw_wall_slice(state, &slice, game, x);
        x++;
    }
}