#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (check_valid_arg(argc, argv) == false)
	{
		ft_putstr_fd(ERR_ARG, 2);
		ft_putstr_fd(P_USAGE, 2);
		return (1);
	}
	init_game(&game);
	if (get_map(&game, argv[1]) == false)
		return (1);
	return (0);
}
