#include "../../include/cub3D_bonus.h"

static void	get_door_nbr(t_game *game);
static void	get_door_info(t_game *game);
static void	set_door_pos(t_game *game, int door_nbr, int y, int x);
static bool	is_door_char(char c);

bool	get_doors(t_game *game)
{
	get_door_nbr(game);
	if (game->door_system.door_counter > 0)
	{
		init_doors(game);
		get_door_info(game);
		return (true);
	}
	return (false);
}

static void	get_door_nbr(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map.matrix[y])
	{
		x = 0;
		while(game->map.matrix[y][x])
		{
			if (is_door_char(game->map.matrix[y][x]))
				game->door_system.door_counter++;
			x++;
		}
		y++;
	}
}

static void	get_door_info(t_game *game)
{
	int	y;
	int	x;
	int	door_nbr;

	door_nbr = 0;
	y = 0;
	while (game->map.matrix[y] && door_nbr < game->door_system.door_counter)
	{
		x = 0;
		while(game->map.matrix[y][x])
		{
			if (is_door_char(game->map.matrix[y][x]))
			{
				set_door_pos(game, door_nbr, y, x);
				door_nbr++;
			}
			x++;
		}
		y++;
	}
}

static void	set_door_pos(t_game *game, int door_nbr, int y, int x)
{
	game->door_system.door[door_nbr].pos.y = (double)y;
	game->door_system.door[door_nbr].pos.x = (double)x;
}

static bool	is_door_char(char c)
{
	return (c == DOOR);
}