#include "../include/cub3D.h"

void	print_matrix(char **matrix)
{
	int	y;

	y = 0;
	while (matrix[y])
		printf("%s", matrix[y++]);
}

void	print_info_list(t_info *info)
{
	t_info	*current_node;

	current_node = info;
	while (current_node)
	{
		printf("%c\n", current_node->identifier);
		if (current_node->found)
			printf("identifier found = true\n");
		else if (!current_node->found)
			printf("identifier found = false\n");
		current_node = current_node->next;
	}
}
