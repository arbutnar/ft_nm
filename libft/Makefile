NAME = libft.a
FLAGS = -Wall -Wextra -Werror

HDR = libft.h
SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_memset.c \
		ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_isdigit.c \
		ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_striteri.c \
		ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_putstr.c \
		ft_strcmp.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

B_SRC = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
		ft_lstlast.c ft_lstnew.c ft_lstsize.c ft_lstmap.c

OBJ = $(SRC:.c=.o)
B_OBJ = $(B_SRC:.c=.o)

P_DIR = ft_printf
P_HDR = $(P_DIR)/ft_printf.h
P_SRC = ft_char.c ft_number.c ft_printf.c ft_utility.c
P_OBJ = $(P_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(B_OBJ) $(P_OBJ)
	ar rcs $@ $(OBJ) $(B_OBJ) $(P_OBJ)

bonus: $(OBJ) $(B_OBJ) $(P_OBJ)
	ar rcs $(NAME) $(OBJ) $(B_OBJ) $(P_OBJ)

%.o: %.c $(HDR)
	gcc $(FLAGS) -I. -c $< -o $@

$(P_OBJ): %.o: $(P_DIR)/%.c $(P_HDR)
	gcc $(FLAGS) -I$(P_DIR) -c $< -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re