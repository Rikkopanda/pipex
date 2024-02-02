
NAME = pip_lib.a
FLAGS = -Wall -Wextra -Werror
LIB = pip_lib.h

SRCS = ft_strlen.c \
	  ft_strnstr.c \
	  ft_strdup.c \
	  ft_calloc.c \
	  ft_strcpy.c \
	  ft_strchr.c \
	  ft_strcat.c \
	  ft_strlcpy.c \
	  ft_strcmp.c \
	  ft_realloc.c \
	  ft_split.c \
	  ft_bzero.c

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)

$(OBJS): %.o: %.c $(LIB)
		cc $(FLAGS) -c $< -o $@

clean:
		/bin/rm -f $(OBJS)

fclean:	clean
		/bin/rm -f $(NAME)

re:		fclean all