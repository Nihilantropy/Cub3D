/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 21:56:04 by crea              #+#    #+#             */
/*   Updated: 2024/03/25 17:30:05 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stddef.h>

/* LIBFT */
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		ft_isascii(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_bzero(void *str, size_t n);
void	*ft_memset(void *str, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void	*ft_memmove(void *dest, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t sz);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t sz);
size_t	ft_strlcat(char *dest, const char *src, size_t sz);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strdup(const char *str);
char	*ft_substr(const char *str, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_itoa(int n);
char	**ft_split(const char *str, char c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *str, char (*f)(unsigned int, char));
void	ft_striteri(char *str, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_putnbr_fd(int n, int fd);

/* PLUS */
int		ft_putchar(char c);
void	ft_exit_error(char *error);
int		ft_isspace(char c);

/* get_next_line */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

typedef struct	s_list {
	char    *data;
	struct  s_list  *next;
}			t_list;
char	*get_next_line(int fd);


#endif
