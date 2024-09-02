CC = /bin/cc
CFLAGS = -Wall -Wextra -Werror -g 

SRCS = src/main.c
OBJS = $(SRCS:.c=.o)

NAME = ./cub3d
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I/usr/include -I$(MLX_DIR) -I$(LIBFT_DIR)/includes

.PHONY: all clean fclean re libft mlx

all: $(NAME)

$(LIBFT):
	$(MAKE) --quiet -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) --quiet -C $(MLX_DIR)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS) $(LIBFT)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -f $(OBJS)
	$(MAKE) --quiet -C $(LIBFT_DIR) clean
	$(MAKE) --quiet -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) --quiet -C $(LIBFT_DIR) fclean
#	$(MAKE) --quiet -C $(MLX_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
