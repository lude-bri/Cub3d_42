# Colors and formatting
RED         = \e[0;31m
GREEN       = \e[0;32m
YELLOW      = \e[0;33m
BLUE        = \e[0;34m
PURPLE      = \e[0;35m
CYAN        = \e[0;36m
WHITE       = \e[0;37m
BOLD        = \e[1m
RESET       = \e[0m

# Cool loading bar animation
LOADING_BAR = @printf "$(CYAN)\r%3d%% [" $$(( $(PROGRESS) * 100 / $(TOTAL) )); \
	for j in $$(seq 1 $$(( $(PROGRESS) * 50 / $(TOTAL) ))); do \
		printf "▰"; \
	done; \
	for j in $$(seq 1 $$(( 50 - $(PROGRESS) * 50 / $(TOTAL) ))); do \
		printf "▱"; \
	done; \
	printf "] $(RESET)"

# Project details
NAME		= cub3D
#BONUS_NAME	= cub3D_bonus

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
MLX_FLAGS	= -L./minilibx-linux -lmlx -lm -lXext -lX11 -I./minilibx-linux
RM			= rm -f

# Directories
SRC_DIR		= src/
OBJ_DIR		= obj/
INC_DIR		= includes/
LIBFT_DIR	= libft/

# Source files
SRC_FILES	= main.c player.c

#BONUS_FILES	= main_bonus.c \
			  parser_bonus.c \
			  utils_bonus.c \
			  texture_bonus.c \
			  raycasting_bonus.c \
			  hooks_bonus.c \
			  map_bonus.c \
			  minimap_bonus.c

SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
#BONUS_SRC	= $(addprefix $(SRC_DIR), $(BONUS_FILES))
#BONUS_OBJ	= $(addprefix $(OBJ_DIR), $(BONUS_FILES:.c=.o))

# Count total files for progress bar
TOTAL		= $(words $(SRC_FILES))
PROGRESS	= 0

# Libft
LIBFT		= $(LIBFT_DIR)libft.a

all: banner $(NAME)

bonus: bonus_banner $(BONUS_NAME)

# Beautiful ASCII art banner
banner:
	@printf "$(PURPLE)"
	@echo "================================================================================"
	@echo "   ██████╗██╗   ██╗██████╗ ██████╗ ██████╗     ███████╗██████╗              "
	@echo "  ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗    ╚════██║██╔══██╗             "
	@echo "  ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║        ██╔╝██║  ██║             "
	@echo "  ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║       ██╔╝ ██║  ██║             "
	@echo "  ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝       ██║  ██████╔╝             "
	@echo "   ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝        ╚═╝  ╚═════╝              "
	@echo "================================================================================"
	@echo "                          $(RED)[ Loading Game Engine ]$(PURPLE)                          "
	@echo "================================================================================"
	@printf "$(RESET)"

bonus_banner:
	@printf "$(CYAN)"
	@echo "================================================================================"
	@echo "   ██████╗██╗   ██╗██████╗ ██████╗ ██████╗     ██████╗  ██████╗ ███╗   ██╗██╗   ██╗███████╗"
	@echo "  ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗    ██╔══██╗██╔═══██╗████╗  ██║██║   ██║██╔════╝"
	@echo "  ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║    ██████╔╝██║   ██║██╔██╗ ██║██║   ██║███████╗"
	@echo "  ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║    ██╔══██╗██║   ██║██║╚██╗██║██║   ██║╚════██║"
	@echo "  ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝    ██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝███████║"
	@echo "   ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝     ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚══════╝"
	@echo "================================================================================"
	@echo "                          $(RED)[ Loading Bonus Features ]$(CYAN)                         "
	@echo "================================================================================"
	@printf "$(RESET)"

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@printf "$(GREEN)\n🎮 Building game engine...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@printf "$(GREEN)🎮 Game successfully compiled!$(RESET)\n"
	@printf "$(YELLOW)🎮 Run ./cub3D <map.cub> to start the game!$(RESET)\n"

$(BONUS_NAME): $(LIBFT) $(OBJ_DIR) $(BONUS_OBJ)
	@printf "$(CYAN)\n🎮 Building bonus features...$(RESET)\n"
	@$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) $(MLX_FLAGS) -o $(BONUS_NAME)
	@printf "$(CYAN)🎮 Bonus features successfully compiled!$(RESET)\n"
	@printf "$(YELLOW)🎮 Run ./cub3D_bonus <map.cub> to start the enhanced game!$(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(eval PROGRESS=$(shell echo $$(($(PROGRESS) + 1))))
	@$(LOADING_BAR)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(LIBFT):
	@printf "$(BLUE)📚 Building libft...$(RESET)\n"
	@make -C $(LIBFT_DIR)

clean:
	@printf "$(RED)🧹 Cleaning object files...$(RESET)\n"
	@$(RM) -r $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@printf "$(GREEN)✨ Cleanup complete!$(RESET)\n"

fclean: clean
	@printf "$(RED)🧹 Removing executables...$(RESET)\n"
	@$(RM) $(NAME) $(BONUS_NAME)
	@make -C $(LIBFT_DIR) fclean
	@printf "$(GREEN)✨ Deep cleanup complete!$(RESET)\n"

re: fclean all

# Help command to show available targets
help:
	@printf "$(BOLD)Available commands:$(RESET)\n"
	@printf "$(GREEN)make$(RESET)        - Build the game\n"
	@printf "$(CYAN)make bonus$(RESET)   - Build the game with bonus features\n"
	@printf "$(YELLOW)make clean$(RESET)    - Remove object files\n"
	@printf "$(RED)make fclean$(RESET)   - Remove object files and executable\n"
	@printf "$(PURPLE)make re$(RESET)       - Rebuild the game\n"
	@printf "$(BLUE)make help$(RESET)     - Show this help message\n"

.PHONY: all bonus clean fclean re help banner bonus_banner

# Easter egg
42:
	@printf "$(YELLOW)"
	@echo "  ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
	@echo "  :::::::::::42 SCHOOL OF INNOVATION AND PROGRAMMING:::::::::::"
	@echo "  ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
	@printf "$(RESET)"