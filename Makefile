NAME = ft_nm

S_DIR = src
O_DIR = obj
O_DIR_64 = $(O_DIR)/64
O_DIR_32 = $(O_DIR)/32

SRCS_LIST = main.c utils.c print.c endian.c process_elf.c symbol.c

SRCS = $(addprefix $(S_DIR)/,$(SRCS_LIST))

NON_GENERIC_SRCS = $(filter %/main.c %/utils.c %/print.c %/endian.c, $(SRCS))
GENERIC_SRCS = $(filter-out %/main.c %/utils.c %/print.c %/endian.c, $(SRCS))

OBJS_NON_GENERIC = $(patsubst $(S_DIR)/%.c, $(O_DIR)/%.o, $(NON_GENERIC_SRCS))
OBJS_64 = $(patsubst $(S_DIR)/%.c, $(O_DIR_64)/%.o, $(GENERIC_SRCS))
OBJS_32 = $(patsubst $(S_DIR)/%.c, $(O_DIR_32)/%.o, $(GENERIC_SRCS))

HDRS = $(wildcard $(S_DIR)/*.h)

LIB_DIV = libft
LIB_ARC = $(LIB_DIV)/libft.a

CFLAGS =  -I$(LIB_DIV) -g
LDFLAGS = -L$(LIB_DIV) -lft

all: $(NAME)

$(NAME): $(LIB_ARC) $(OBJS_NON_GENERIC) $(OBJS_64) $(OBJS_32)
	gcc $(CFLAGS) -o $@ $(OBJS_NON_GENERIC) $(OBJS_64) $(OBJS_32) $(LDFLAGS)

$(LIB_ARC):
	make -C $(LIB_DIV)

$(O_DIR)/%.o: $(S_DIR)/%.c $(HDRS)
	@mkdir -p $(O_DIR)
	gcc $(CFLAGS) -c $< -o $@

$(O_DIR_64)/%.o: $(S_DIR)/%.c $(HDRS)
	@mkdir -p $(O_DIR_64)
	gcc $(CFLAGS) -c $< -o $@

$(O_DIR_32)/%.o: $(S_DIR)/%.c $(HDRS)
	@mkdir -p $(O_DIR_32)
	gcc $(CFLAGS) -D X32 -c $< -o $@

CONTAINER_IMG = ft_nm_image

container-clean:
	@docker rm -f $(NAME) 1>/dev/null

container:
	@docker build -t $(CONTAINER_IMG) .
	@docker run -d --name $(NAME) $(CONTAINER_IMG)

exec:
	@docker exec -it $(NAME) /bin/bash

tester: $(NAME)
	@test -d nm_tester || git clone https://github.com/jemercie/nm_tester.git
	cd nm_tester && ./run all

clean:
	rm -rf $(O_DIR)
	make clean -C $(LIB_DIV)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIB_DIV)
	rm -rf nm_tester

re: fclean all

.PHONY: all clean fclean re container exec tester