#include "../include/cub3D.h"

static void	set_player_var(t_game *game, int y, int x);
static void	set_player_rot(t_game *game, char face);
static void	set_player_pos(t_game *game, int y, int x);

/**
 * @brief parse matrix to get and set palyer infos;
 * - player number
 * - player facing
 * - player velocity
 * - camera field of view
 * - player position
 * - player rotation
 * Remove the player char from the map matrix
 */
void	get_player_infos(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map.matrix[y])
	{
		x = 0;
		while (game->map.matrix[y][x])
		{
			if (is_player_char(game->map.matrix[y][x]))
			{
				game->map.check.player++;
				set_player_var(game, y, x);
				game->map.matrix[y][x] = FLOOR;
				return ;
			}
			x++;
		}
		y++;
	}
}

bool	is_player_char(char player)
{
	return (player == NORTH || player == EAST
		|| player == SOUTH || player == WEST);
}

static void	set_player_var(t_game *game, int y, int x)
{
	game->player.face = game->map.matrix[y][x];
	game->player.speed = P_SPEED;
	game->player.rot_speed = R_SPEED;
	game->player.camera.fov = P_FOV;
	set_player_pos(game, y, x);
	set_player_rot(game, game->player.face);	
}

static void	set_player_pos(t_game *game, int y, int x)
{
	game->player.pos.y = y + 0.5;
	game->player.pos.x = x + 0.5;
}

static void	set_player_rot(t_game *game, char face)
{
	double	rot;

	rot = 0.0;
	if (face == NORTH)
		rot = -M_PI / 2;
	else if (face == EAST)
		rot = 0.0;
	else if (face == SOUTH)
		rot = M_PI / 2;
	else if (face == WEST)
		rot = M_PI;
	game->player.rot.current_angle = rot;
}
