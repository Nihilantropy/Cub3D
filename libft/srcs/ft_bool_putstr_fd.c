/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bool_putstr_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 10:38:25 by crea              #+#    #+#             */
/*   Updated: 2024/09/07 10:43:18 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

bool	ft_bool_putstr_fd(char *str, int fd)
{
	while (*str)
		write(fd, &*str++, 1);
	if (fd == 2)
		return (false);
	return (true);
}
