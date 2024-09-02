NAME = ./cub3d
CC = /bin/cc
CFLAGS = -Wall -Wextra -Werror

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m

SRC = main.c

OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling source files...$(NC)"
	@$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@echo "$(GREEN)Compilation is complete. Generated executable: $(NAME).$(NC)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR):
	@/bin/mkdir -p $(OBJ_DIR)

clean:
	@echo "$(YELLOW)Cleaning object files...$(NC)"
	@/bin/rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Cleaning complete.$(NC)"

fclean: clean
	@echo "$(YELLOW)Removing executable $(NAME)...$(NC)"
	@/bin/rm -f $(NAME)
	@echo "$(GREEN)Removal complete.$(NC)"

re: fclean all

.PHONY: all clean fclean re