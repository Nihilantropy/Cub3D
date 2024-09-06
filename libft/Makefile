NAME		= libft.a

LIBFT_DIR	= ./srcs

SRCS		= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isprint.c ft_isascii.c ft_memset.c ft_strlen.c \
				ft_atoi.c ft_memset.c ft_bzero.c ft_memmove.c ft_memcpy.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c \
				ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_calloc.c \
				ft_strdup.c ft_substr.c ft_strjoin.c ft_itoa.c ft_split.c ft_strtrim.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
				ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putchar.c get_next_line.c get_next_line_utils.c ft_exit_result.c ft_isspace.c

OBJS		= $(patsubst %.c, $(LIBFT_DIR)/%.o, $(SRCS))

B_OBJS		= $(patsubst %.c, $(LIBFT_DIR)/%.o, $(B_SRCS))

HEADER_DIR	= ./include

HEADER		= libft.h

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

AR			= ar rcs

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)

%.o: 		%.c $(HEADER_DIR)
			$(CC) -c $< $(CFLAGS) -o $@  -I$(HEADER)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re