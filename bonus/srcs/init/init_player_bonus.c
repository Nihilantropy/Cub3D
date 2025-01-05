#include "../../include/cub3D_bonus.h"

static void	init_camera(t_game *game);

void init_player(t_game *game)
{
	game->player.face = 0;
	game->player.pos.x = 0.0;
	game->player.pos.y = 0.0;
	game->player.pos.x_screen = 0;
	game->player.pos.y_screen = 0;
	game->player.speed = 0.0;
	game->player.rot_speed = 0.0;
	game->player.moving.forward = false;
	game->player.moving.backward = false;
	init_camera(game);
}

static void	init_camera(t_game *game)
{
	game->player.camera.dir_x = 0.0;
	game->player.camera.dir_y = 0.0;
	game->player.camera.plane_x = 0.0;
	game->player.camera.plane_y = 0.0;
	game->player.camera.ray_dir_x = 0.0;
	game->player.camera.ray_dir_y = 0.0;
	game->player.camera.delta_dist_x = 0.0;
	game->player.camera.delta_dist_y = 0.0;
	game->player.camera.side_dist_x = 0.0;
	game->player.camera.side_dist_y = 0.0;
	game->player.camera.map_x = 0;
	game->player.camera.map_y = 0;
	game->player.camera.step_x = 0;
	game->player.camera.step_y = 0;
	game->player.camera.perp_wall_dist = 0.0;
	game->player.camera.side = 0;
	game->player.camera.hit_type = 0;
	game->player.camera.perp_door_dist = 0.0;
	game->player.camera.door_hit = false;
	game->player.camera.door_side = 0;
	game->player.camera.door_frame = 0;
}
