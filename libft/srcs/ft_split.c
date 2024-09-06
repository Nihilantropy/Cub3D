/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 20:01:44 by crea              #+#    #+#             */
/*   Updated: 2024/02/05 14:43:16 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	count_words(const char *str, char c)
{
	size_t	words_count;
	int		sep;

	words_count = 0;
	sep = 1;
	while (*str)
	{
		if (*str != c && sep != 0)
		{
			sep = 0;
			words_count++;
		}
		else if (*str == c)
			sep = 1;
		str++;
	}
	return (words_count);
}

static void	make_words(char **words, const char *str, char c, size_t words_nb)
{
	char	*ptr_c;

	while (*str && *str == c)
		str++;
	while (words_nb-- != 0)
	{
		ptr_c = ft_strchr(str, c);
		if (ptr_c != 0)
		{
			*words = ft_substr(str, 0, (ptr_c - str));
			while (*ptr_c && *ptr_c == c)
				ptr_c++;
			str = ptr_c;
		}
		else
			*words = ft_substr(str, 0, (ft_strlen(str) + 1));
		words++;
	}
	*words = NULL;
}

char	**ft_split(const char *str, char c)
{
	size_t	words_nb;
	char	**words;

	if (!str)
		return (0);
	words_nb = count_words(str, c);
	words = malloc(sizeof(char **) * (words_nb + 1));
	if (!words)
		return (0);
	make_words(words, str, c, words_nb);
	return (words);
}
