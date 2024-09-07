#include "../include/cub3D.h"

void	free_matrix(char **matrix)
{
	int	y;

	y = 0;
	while (matrix[y])
		free(matrix[y++]);
	matrix = NULL;
}

void	free_info_list(t_info **info)
{
	t_info	*current;
	t_info	*next;

	if (!*info)
		return;
	current = *info;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*info = NULL;
}
