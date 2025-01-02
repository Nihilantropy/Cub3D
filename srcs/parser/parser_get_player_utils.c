#include "../include/cub3D.h"

void	set_north_rot(t_game *game)
{
	game->player.camera.dir_x = 0.0;
	game->player.camera.dir_y = -1.0;
	game->player.camera.plane_x = 0.66;
	game->player.camera.plane_y = 0.0;
}

void	set_east_rot(t_game *game)
{
	game->player.camera.dir_x = 1.0;
	game->player.camera.dir_y = 0.0;
	game->player.camera.plane_x = 0.0;
	game->player.camera.plane_y = 0.66;	
}

void	set_south_rot(t_game *game)
{
	game->player.camera.dir_x = 0.0;
	game->player.camera.dir_y = 1.0;
	game->player.camera.plane_x = -0.66;
	game->player.camera.plane_y = 0.0;	
}

void	set_west_rot(t_game *game)
{
	game->player.camera.dir_x = -1.0;
	game->player.camera.dir_y = 0.0;
	game->player.camera.plane_x = 0.0;
	game->player.camera.plane_y = -0.66;	
}