#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (valid_check(argc, argv) == 1)
	{
		ft_putstr_fd(ERR_ARG, 2);
		ft_putstr_fd(P_USAGE, 2);
		return (1);
	}
	game = init_game();
	get_map(game, argv[1]);
	return (0);
}
