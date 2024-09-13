#include "../include/cub3D.h"

void	free_all(t_game *game)
{
	free_matrix((char **)game->map.matrix);
	free_info_list(&game->map.check.info);
}

void	free_matrix(char **matrix)
{
	int	y;

	y = 0;
	if (!matrix[y])
		return ;
	while (matrix[y])
		free(matrix[y++]);
	free(matrix);
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
