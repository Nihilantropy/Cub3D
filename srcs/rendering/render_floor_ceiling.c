#include "../include/cub3D.h"

static void draw_ceiling_line(t_render_state *state, t_game *game,
    int y, int width)
{
	(void)game;
    int x;

    x = 0;
    while (x < width)
    {
        state->img_data[y * width + x] = GRAY;  // Ceiling color
        x++;
    }
}

static void draw_floor_line(t_render_state *state, t_game *game,
    int y, int width)
{
	(void)game;
    int x;

    x = 0;
    while (x < width)
    {
        state->img_data[y * width + x] = GREEN;  // Floor color
        x++;
    }
}

void render_floor_ceiling(t_game *game, t_render_state *state)
{
    int y;
    int mid_point;

    mid_point = game->display.height / 2;
    y = 0;
    while (y < game->display.height)
    {
        if (y < mid_point)
            draw_ceiling_line(state, game, y, game->display.width);
        else
            draw_floor_line(state, game, y, game->display.width);
        y++;
    }
}