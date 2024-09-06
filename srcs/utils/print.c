#include "../include/cub3D.h"

void	print_matrix(char **matrix)
{
	int	y;

	y = 0;
	while (matrix[y])
		printf("%s", matrix[y++]);
}
