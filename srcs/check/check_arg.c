#include "../include/cub3D.h"

static bool	check_extention(char *str);

/*	valid check:
**	return 1 if argument passed or
**	map extention are not valid
*/
bool	check_valid_arg(int argc, char **argv)
{
	if (argc != 2)
		return (false);
	else if (check_extention(argv[1]) == false)
		return (false);
	return (true);
}

static bool	check_extention(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (i < 4)
		return (1);
	if (str[i] == 'b' && str[i - 1] == 'u' && str[i - 2] == 'c'
		&& str[i - 3] == '.')
		return (true);
	else
		return (false);
}