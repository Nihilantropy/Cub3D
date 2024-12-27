#include "../include/cub3D.h"

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
	char	**copy_matrix;
	int		y;

	copy_matrix = NULL;
	y = 0;
	while (matrix[y])
		y++;
	copy_matrix = malloc(sizeof(char *) * (y + 1));
	if (!copy_matrix)
		ft_exit_error(ERR_ALLOC_MATRIX_COPY);
	y = 0;
	while (matrix[y])
	{
		copy_matrix[y] = ft_strdup(matrix[y]);
		y++;
	}
	copy_matrix[y] = NULL;
	return (copy_matrix);
}