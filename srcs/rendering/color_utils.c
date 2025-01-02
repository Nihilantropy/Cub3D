#include "../include/cub3D.h"

static int apply_distance_fog(int color, double distance)
{
    int r, g, b;
    double fog_factor;

    fog_factor = fmin(1.0, distance / 20.0);  // Fog starts at distance 20
    r = ((color >> 16) & 0xFF) * (1 - fog_factor);
    g = ((color >> 8) & 0xFF) * (1 - fog_factor);
    b = (color & 0xFF) * (1 - fog_factor);

    return (r << 16) | (g << 8) | b;
}

static int get_base_wall_color(int side)
{
    if (side == 0)  // North-South walls
        return RED;
    return YELLOW;  // East-West walls
}

int determine_wall_color(int side, double distance)
{
    int base_color;

    base_color = get_base_wall_color(side);
    return apply_distance_fog(base_color, distance);
}