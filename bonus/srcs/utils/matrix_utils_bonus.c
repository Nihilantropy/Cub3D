#include "../../include/cub3D_bonus.h"

void	print_matrix(const char **matrix)
{
	int	y;

	y = 0;
	while (matrix[y])
		printf("%s\n", matrix[y++]);
}

void	free_matrix(char **matrix)
{
	int	y;

	if (!matrix || !*matrix)
		return ;
	y = 0;
	while (matrix[y])
		free(matrix[y++]);
	free(matrix);
	matrix = NULL;
}

void	free_bool_matrix(bool **matrix)
{
	int y;
	
	if (!matrix)
		return ;
	y = 0;
	while (matrix[y])
		free(matrix[y++]);
	free(matrix);
	matrix = NULL;
}

char	**dup_matrix(const char **matrix)
{
	char	**dup_matrix;
	int		y;

	dup_matrix = NULL;
	y = 0;
	while (matrix[y])
		y++;
	dup_matrix = malloc(sizeof(char *) * (y + 1));
	if (!dup_matrix)
		ft_exit_error(ERR_ALLOC_MATRIX_DUP);
	y = 0;
	while (matrix[y])
	{
		dup_matrix[y] = ft_strdup(matrix[y]);
		y++;
	}
	dup_matrix[y] = NULL;
	return (dup_matrix);
}