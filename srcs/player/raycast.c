#include "../include/cub3D.h"

static void perform_dda(t_game *game, t_player *player);
static void calc_perp_dist(t_player *player);
static void stores_wall_hit_coord(t_player *player);

/**
 * @brief Cast a single ray from the player's position and check for wall collision.
 */
void cast_ray(t_game *game, t_player *player)
{
    // Prevent potential division by zero
    if (fabs(cos(player->rot.current_angle)) < 1e-10)
        player->camera.ray_dir_x = 1e-10;
    else
        player->camera.ray_dir_x = cos(player->rot.current_angle);

    if (fabs(sin(player->rot.current_angle)) < 1e-10)
        player->camera.ray_dir_y = 1e-10;
    else
        player->camera.ray_dir_y = sin(player->rot.current_angle);

    // Prevent potential division by zero in delta distance calculations
    player->camera.delta_dist_x = fabs(1.0 / player->camera.ray_dir_x);
    player->camera.delta_dist_y = fabs(1.0 / player->camera.ray_dir_y);

    player->camera.map_x = (int)player->pos.x;
    player->camera.map_y = (int)player->pos.y;

    // Calculate step and initial side distances
    if (player->camera.ray_dir_x < 0)
    {
        player->camera.step_x = -1;
        player->camera.side_dist_x = (player->pos.x - player->camera.map_x) * player->camera.delta_dist_x;
    }
    else
    {
        player->camera.step_x = 1;
        player->camera.side_dist_x = (player->camera.map_x + 1.0 - player->pos.x) * player->camera.delta_dist_x;
    }

    if (player->camera.ray_dir_y < 0)
    {
        player->camera.step_y = -1;
        player->camera.side_dist_y = (player->pos.y - player->camera.map_y) * player->camera.delta_dist_y;
    }
    else
    {
        player->camera.step_y = 1;
        player->camera.side_dist_y = (player->camera.map_y + 1.0 - player->pos.y) * player->camera.delta_dist_y;
    }

    perform_dda(game, player);
}

static void perform_dda(t_game *game, t_player *player)
{
    bool hit = false;
    int max_iterations = game->map.width + game->map.height; // Prevent infinite loop

    while (!hit && max_iterations > 0)
    {
        // Choose smallest side distance
        if (player->camera.side_dist_x < player->camera.side_dist_y)
        {
            player->camera.side_dist_x += player->camera.delta_dist_x;
            player->camera.map_x += player->camera.step_x;
        }
        else
        {
            player->camera.side_dist_y += player->camera.delta_dist_y;
            player->camera.map_y += player->camera.step_y;
        }

        // Boundary check with more robust error handling
        if (player->camera.map_x < 0 || player->camera.map_x >= game->map.width ||
            player->camera.map_y < 0 || player->camera.map_y >= game->map.height)
        {
            game->error_state = 1;
            return;
        }

        // Wall hit detection
        if (game->map.matrix[player->camera.map_y][player->camera.map_x] == WALL)
        {
            hit = true;
            calc_perp_dist(player);
            stores_wall_hit_coord(player);
        }

        max_iterations--;
    }

    // Handle case where no wall was found
    if (!hit)
    {
        game->error_state = 1;
    }
}

/**
 * @brief calculate the perpendicular distance from the player
 */
static void calc_perp_dist(t_player *player)
{
    // Use absolute value to prevent potential negative distance
    if (player->camera.side_dist_x < player->camera.side_dist_y)
        player->camera.perp_wall_dist = fabs(player->camera.side_dist_x - player->camera.delta_dist_x);
    else
        player->camera.perp_wall_dist = fabs(player->camera.side_dist_y - player->camera.delta_dist_y);
}

static void stores_wall_hit_coord(t_player *player)
{
    if (player->camera.side_dist_x < player->camera.side_dist_y)
    {
        player->camera.wall_hit_x = (double)player->camera.map_x;
        player->camera.wall_hit_y = player->pos.y +
            player->camera.perp_wall_dist * player->camera.ray_dir_y;
    }
    else
    {
        player->camera.wall_hit_y = (double)player->camera.map_y;
        player->camera.wall_hit_x = player->pos.x +
            player->camera.perp_wall_dist * player->camera.ray_dir_x;
    }
}
