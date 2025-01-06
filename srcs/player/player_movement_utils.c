#include "../include/cub3D.h"

void	move_step_forward(t_player *player, double *step_x, double *step_y)
{
	*step_x = player->camera.dir_x * player->speed;
	*step_y = player->camera.dir_y * player->speed;
}

void	move_step_backward(t_player *player, double *step_x, double *step_y)
{
	*step_x = -player->camera.dir_x * player->speed;
	*step_y = -player->camera.dir_y * player->speed;
}

void	move_step_left(t_player *player, double *step_x, double *step_y)
{
	*step_x = -player->camera.plane_x * player->speed;
	*step_y = -player->camera.plane_y * player->speed;
}

void	move_step_right(t_player *player, double *step_x, double *step_y)
{
	*step_x = player->camera.plane_x * player->speed;
	*step_y = player->camera.plane_y * player->speed;
}

void	move_step_still(double *step_x, double *step_y)
{
	*step_x = 0;
	*step_y = 0;
}
