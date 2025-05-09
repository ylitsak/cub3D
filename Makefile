NAME 		= cub3D
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
MLX42_FLAGS	= -ldl -lglfw -pthread -lm
INCLUDE 	= -I./includes -I./libft/includes -I./MLX42/include/MLX42

OBJ_DIR 	= objects
OBJS 		= $(addprefix $(OBJ_DIR)/,  $(SRCS_DIR:.c=.o))
LIBFT 		= ./libft/libft.a
MLX42 		= ./MLX42/build/libmlx42.a
BUILD 		= ./MLX42/build

SRCS_DIR = srcs/main.c \
			srcs/parse/file_validation.c	srcs/parse/parse_error.c	\
			srcs/parse/parse_utils.c	srcs/parse/read_map_file.c	\
			srcs/parse/extract_element.c	srcs/parse/map_validation.c	\
			srcs/parse/extract_map.c	srcs/parse/map_path_validation.c\
			srcs/parse/validate_element.c	\
			srcs/cub/cub_start.c	srcs/cub/raycasting.c	\
			srcs/cub/player_movement.c	srcs/cub/raycast_utils.c\
			srcs/cub/cub_error.c	srcs/cub/draw_walls.c	\
			srcs/cub/draw_floor_ceiling.c	srcs/cub/valid_position.c\

SRCS 		= $(SRCS_DIR)

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft

$(MLX42):
	cd MLX42 && cmake -B build
	cd MLX42 && cmake --build build -j4
	@$(MAKE) -C MLX42/build -j4

$(NAME): $(OBJS) $(LIBFT) $(MLX42)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT) $(MLX42) $(MLX42_FLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C ./libft
	@if [ -d ./MLX42/build ]; then $(MAKE) clean -C ./MLX42/build; fi

fclean: clean
	rm -rf $(NAME) $(LIBFT) $(BUILD)

re: fclean all

.PHONY: clean fclean re all
