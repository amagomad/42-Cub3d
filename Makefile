NAME            := cub3d
CC              := cc
CFLAGS          := -Wall -Werror -Wextra -Iinclude -g #-fsanitize=address


# OS detection
UNAME_S         := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    MLX_FLAGS  := -ldl -lglfw -pthread -lm
else ifeq ($(UNAME_S), Darwin)
    MLX_FLAGS  := -lglfw -framework Cocoa -framework OpenGL -framework IOKit
endif

#MLX_FLAGS      := -ldl -lglfw -pthread -lm
#MLX_FLAGS		:=  -lglfw -framework Cocoa -framework OpenGL -framework IOKit
MLX42_PATH = MLX42

DIR_LIBFT       := libft
LIBFT_LIB       := $(DIR_LIBFT)/libft.a
DIR_SRCS        := src
DIR_OBJS        := .objs
DIR_INCS        := includes

LST_SRCS        := cub3d.c \
					parse/utils.c \
					parse/parsing.c \
					parse/check.c \

LST_OBJS        := $(LST_SRCS:.c=.o)

LST_INCS        := cub3d.h
SRCS            := $(addprefix $(DIR_SRCS)/,$(LST_SRCS))
OBJS            := $(addprefix $(DIR_OBJS)/,$(LST_OBJS))
INCS            := $(addprefix $(DIR_INCS)/,$(LST_INCS))

ERASE           := \033[2K\r
BLUE            := \033[34m
YELLOW          := \033[33m
GREEN           := \033[32m
END             := \033[0m

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c $(INCS) Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(DIR_INCS) -c $< -o $@
	printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(DIR_LIBFT) --no-print-directory

mlx : 
	@git clone https://github.com/codam-coding-college/MLX42.git
	cmake $(MLX42_PATH) -B $(MLX42_PATH)/build
	cmake --build $(MLX42_PATH)/build -j4

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBFT_LIB) $(MLX42_PATH)/build/libmlx42.a $(MLX_FLAGS)
	printf "$(ERASE)$(GREEN)$@ made\n$(END)"

clean:
	rm -rf $(DIR_OBJS)
	printf "$(YELLOW)$(DIR_OBJS) removed$(END)\n"
	$(MAKE) -C $(DIR_LIBFT) clean --no-print-directory

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(DIR_LIBFT) fclean --no-print-directory
	printf "$(YELLOW)$(NAME) & libft.a removed$(END)\n"

re: fclean all

.PHONY: all clean fclean re
.SILENT:
