#include "../include/cub3D.h"

static int	check_extention(char *str);

/*	valid check:
		return 1 if argument passed or
		map extention are not valid
*/
int	valid_check(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	else if (check_extention(argv[1]) == 1)
		return (1);
	return (0);
}

static int	check_extention(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (i < 4)
		return (1);
	if (str[i] == 'b' && str[i - 1] == 'u' && str[i - 2] == 'c'
		&& str[i - 3] == '.')
		return (0);
	else
		return (1);
}