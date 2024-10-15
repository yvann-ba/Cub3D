CC = clang
CFLAGS = -Wall -Wextra -Werror

SRCS = src/main.c src/parsing/open_file_check_format.c \
		src/parsing/pars_clean_exit.c src/parsing/file_to_string.c \
		src/parsing/string_to_tab.c  src/parsing/grab_file_data.c \
		src/parsing/grab_file_data_map.c \
		src/parsing/utils_parse.c \
		src/parsing/take_color_values.c \
		src/parsing/open_textures.c \
		src/parsing/check_store_path.c \
		src/parsing/contains_only_these_characters.c \
		src/parsing/grab_file_data_color.c \
		src/init_graphics.c \
		src/init_graphics_two.c \
		src/parsing/flood_fill.c \
		src/key_move.c src/ray_utils.c \
		src/player_utils.c \
		src/ray_calculation.c \
		src/map_utils.c src/raycasting.c

OBJ_DIR = build
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

NAME = ./cub3D
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a 
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I/usr/include -I$(MLX_DIR) -I$(LIBFT_DIR)/includes

.PHONY: all clean fclean re libft mlx

all: $(NAME)

$(LIBFT):
	$(MAKE) --quiet -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) --quiet -C $(MLX_DIR)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D)  # Ensure the directory for the object file exists
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS) $(LIBFT)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) --quiet -C $(LIBFT_DIR) clean
	$(MAKE) --quiet -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) --quiet -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
