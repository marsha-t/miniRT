NAME = miniRT

CC = cc
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -O1
CFLAGS = -Wall -Wextra -Werror

MINIRT_SRCS = 	./src/miniRT.c \
				./src/parse/check_args.c \
				./src/parse/check_objects.c \
				./src/parse/create_objects.c \
				./src/parse/fill_settings.c \
				./src/parse/free_utils.c \
				./src/parse/print_utils.c \
				./src/intersect/prepare.c \
				./src/intersect/img.c \
				./src/intersect/intersect.c \
				./src/intersect/intersect_math.c \
				./src/intersect/intersect_prepare.c \
				./src/intersect/intersect_utils.c \
				./src/light/final_colour.c \
				./src/light/shadow.c \
				./src/utils/misc_math.c \
				./src/utils/vector_op.c \
				./src/utils/vector_utils.c

MINIRT_OBJS = $(MINIRT_SRCS:.c=.o)
VPATH = src:lib:lib/libft

# includes for mlx mac
INCLUDES = -I/opt/X11/include -Imlx
# includes for mlx linux
# INCLUDES = -I/usr/include -Imlx -O3

# mlxflags for mac
MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
# mlxflags for linux
# MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

MLX_DIR = ./mlx
# MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_LIB = $(MLX_DIR)/libmlx.a

### LIBFT
LIBFT = libft.a
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/$(LIBFT)
LIBR = $(LIBFT_LIB)
### LIBFT

MAKE_LIBR = make --no-print-directory -C

RM = rm -rf

LB = ar rcs

all: $(LIBFT_LIB) $(MLX_LIB) $(NAME)

$(NAME): $(MINIRT_OBJS)
		$(CC) $(CFLAGS) $(MINIRT_OBJS) $(MLX_FLAGS) $(LIBFT_LIB) -o $(NAME) -lm

$(LIBFT_LIB):
	$(MAKE_LIBR) $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE_LIBR) $(MLX_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(MINIRT_OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME) $(MINIRT_OBJS)
	$(MAKE_LIBR) $(LIBFT_DIR) fclean

re: fclean all
	clear