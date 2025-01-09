/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:57:31 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 13:57:37 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	print_info_list(t_info *info)
{
	t_info	*current_node;

	current_node = info;
	while (current_node)
	{
		printf("identifier: %c\n", current_node->identifier);
		if (current_node->content)
			printf("content: %s\n", current_node->content);
		if (current_node->found)
			printf("identifier found = true\n");
		else if (!current_node->found)
			printf("identifier found = false\n");
		current_node = current_node->next;
	}
}

void	free_info_list(t_info **info)
{
	t_info	*current;
	t_info	*next;

	if (!*info)
		return ;
	current = *info;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
	*info = NULL;
}
