#include "../include/cub3D.h"

void	free_matrix(char **matrix)
{
	int	y;

	y = 0;
	while (matrix[y])
		free(matrix[y++]);
	matrix = NULL;
}
