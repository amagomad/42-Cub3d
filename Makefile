# Compiler and flags
CC              = cc
CFLAGS          = -Wall -Werror -Wextra -g -O3 -march=native -mtune=native -flto -ffast-math -funroll-loops -fomit-frame-pointer -malign-double -fsanitize=address
INCLUDE_FLAGS   = -I$(DIR_INCS) -I$(MLX42_PATH)/include

# OS detection
UNAME_S         = $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MLX_FLAGS   = -ldl -lglfw -pthread -lm
else ifeq ($(UNAME_S), Darwin)
	MLX_FLAGS   = -lglfw -framework Cocoa -framework OpenGL -framework IOKit
endif

# Project structure
NAME            = cub3d
MLX42_PATH      = .MLX42
DIR_LIBFT       = libft
LIBFT_LIB       = $(DIR_LIBFT)/libft.a
DIR_SRCS        = src
DIR_SRCS_BONUS  = src_bonus
DIR_OBJS        = .objs
DIR_OBJS_BONUS  = .objs_bonus
DIR_INCS        = includes

# Source groupings
INIT_GAME       = cub3d.c init_game/init_game.c
PARSING         = parse/parsing.c parse/check.c parse/map.c parse/texture.c parse/color.c parse/description.c parse/player.c
MENU            = menu/menu.c
MINIMAP         = minimap/minimap.c minimap/draw_player.c
DOORS           = doors/doors.c
KEYPRESS        = keypress/move.c keypress/handle_keypress.c
RAYCASTING      = raycasting/raycasting.c raycasting/draw.c
UTILS           = utils/free.c utils/utils.c utils/mlx_utils.c
SPRITE          = sprite/sprite.c sprite/sprite_utils.c sprite/sprite_utils_2.c sprite/sprite_utils_3.c

# File lists
LST_SRCS        = $(INIT_GAME) $(PARSING) $(KEYPRESS) $(RAYCASTING) $(UTILS)
LST_SRCS_BONUS  = $(INIT_GAME) $(PARSING) $(MENU) $(MINIMAP) $(DOORS) $(KEYPRESS) $(RAYCASTING) $(UTILS) $(SPRITE)

OBJS            = $(addprefix $(DIR_OBJS)/,$(LST_SRCS:.c=.o))
OBJS_BONUS      = $(addprefix $(DIR_OBJS_BONUS)/,$(LST_SRCS_BONUS:.c=.o))

# Color codes
ERASE           = \033[2K\r
BLUE            = \033[34m
YELLOW          = \033[33m
GREEN           = \033[32m
END             = \033[0m

# Main targets
all: $(LIBFT_LIB) $(NAME)

bonus: $(LIBFT_LIB) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME) $(LIBFT_LIB) $(MLX42_PATH)/build/libmlx42.a $(MLX_FLAGS)
	printf "$(ERASE)$(GREEN)Bonus version built\n$(END)"

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBFT_LIB) $(MLX42_PATH)/build/libmlx42.a $(MLX_FLAGS)
	printf "$(ERASE)$(GREEN)Main version built\n$(END)"

# Compilation rules
$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@
	printf "$(ERASE)$(BLUE)Compiling:$(END) %s" "$<"

$(DIR_OBJS_BONUS)/%.o: $(DIR_SRCS_BONUS)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@
	printf "$(ERASE)$(BLUE)Compiling bonus:$(END) %s" "$<"

# Dependencies
$(LIBFT_LIB):
	$(MAKE) -C $(DIR_LIBFT) --no-print-directory

mlx:
	if [ -d ".MLX42" ]; then \
		rm -rf .MLX42; \
	fi
	if [ ! -d "$(MLX42_PATH)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_PATH); \
	fi
	cmake -S $(MLX42_PATH) -B $(MLX42_PATH)/build
	cmake --build $(MLX42_PATH)/build -j4

# Clean rules
clean:
	rm -rf $(DIR_OBJS) $(DIR_OBJS_BONUS)
	$(MAKE) -C $(DIR_LIBFT) clean --no-print-directory
	printf "$(YELLOW)Object files removed\n$(END)"

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(DIR_LIBFT) fclean --no-print-directory
	printf "$(YELLOW)Executable and libraries removed\n$(END)"

re: fclean all

.PHONY: all bonus clean fclean re mlx
.SILENT:
