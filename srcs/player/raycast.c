#include "../include/cub3D.h"

static void	perform_dda(t_game *game, t_player *player);
static void	calc_perp_dist(t_player *player);
static void	stores_wall_hit_coord(t_player *player);

/**
 * @brief Cast a single ray from the player's position and check for wall collision.
 */
void	cast_ray(t_game *game, t_player *player)
{
	player->camera.ray_dir_x = cos(player->rot.current_angle);
	player->camera.ray_dir_y = sin(player->rot.current_angle);
	player->camera.delta_dist_x = fabs(1 / player->camera.ray_dir_x);
	player->camera.delta_dist_y = fabs(1 / player->camera.ray_dir_y);
	player->camera.map_x = (int)player->pos.x;
	player->camera.map_y = (int)player->pos.y;

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
	draw_ray(game, player);
}

static void	perform_dda(t_game *game, t_player *player)
{
	bool	hit;

	hit = false;
	while (!hit)
	{
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
		if (player->camera.map_x < 0 || player->camera.map_x >= game->map.width ||
			player->camera.map_y < 0 || player->camera.map_y >= game->map.height)
		{
			perror(ERR_INVALID_RAY_CAST_ACCESS);
			close_game(game);
			return;
		}
		if (game->map.matrix[player->camera.map_y][player->camera.map_x] == WALL)
		{
			hit = true;
			calc_perp_dist(player);
			stores_wall_hit_coord(player);
		}
	}
}

static void	calc_perp_dist(t_player *player)
{
	if (player->camera.side_dist_x < player->camera.side_dist_y)
		player->camera.perp_wall_dist = player->camera.side_dist_x - player->camera.delta_dist_x;
	else
		player->camera.perp_wall_dist = player->camera.side_dist_y - player->camera.delta_dist_y;
}

static void	stores_wall_hit_coord(t_player *player)
{
	if (player->camera.side_dist_x < player->camera.side_dist_y)
	{
		player->camera.wall_hit_x = player->camera.map_x;
		player->camera.wall_hit_y = player->pos.y +
			player->camera.perp_wall_dist * player->camera.ray_dir_y;
	}
	else
	{
		player->camera.wall_hit_x = player->pos.x +
			player->camera.perp_wall_dist * player->camera.ray_dir_x;
		player->camera.wall_hit_y = player->camera.map_y;
	}
}
