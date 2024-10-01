NAME = miniRT

CC = cc
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -O1
CFLAGS = -Wall -Wextra -Werror -I/usr/include -Imlx

MINIRT_SRCS = 	./src/miniRT.c \
				./src/parse/check_args.c \
				./src/parse/check_objects.c \
				./src/parse/check_coord.c \
				./src/parse/check_norm.c \
				./src/parse/check_colour.c \
				./src/parse/create_objects.c \
				./src/parse/init_objects.c \
				./src/parse/create_plane.c \
				./src/parse/create_sphere.c \
				./src/parse/create_cylinder.c \
				./src/parse/create_cone.c \
				./src/parse/create_light.c \
				./src/parse/create_spotlight.c \
				./src/parse/fill_settings.c \
				./src/parse/fill_camera_ambient.c \
				./src/parse/free_utils.c \
				./src/parse/free_objects.c \
				./src/parse/free_exit.c \
				./src/parse/print_utils.c \
				./src/parse/print_banner.c \
				./src/parse/data_init.c \
				./src/parse/parse.c \
				./src/parse/mlx_init.c \
				./src/intersect/prepare1.c \
				./src/intersect/prepare2.c \
				./src/intersect/img.c \
				./src/intersect/interpolate.c \
				./src/intersect/intersect.c \
				./src/intersect/intersect_obj.c \
				./src/intersect/intersect_math1.c \
				./src/intersect/intersect_math2.c \
				./src/intersect/intersect_prepare.c \
				./src/intersect/get_normal.c \
				./src/intersect/intersect_utils.c \
				./src/intersect/render.c \
				./src/light/final_colour.c \
				./src/light/diffuse_specular.c \
				./src/light/shadow.c \
				./src/light/shadow_obj.c \
				./src/light/checkerboard1.c\
				./src/light/checkerboard2.c\
				./src/light/uv_map1.c\
				./src/light/uv_map2.c\
				./src/intersect/bumpmap.c \
				./src/intersect/bumpmap_utils.c \
				./src/utils/misc_math.c \
				./src/utils/vector_op1.c \
				./src/utils/vector_op2.c \
				./src/utils/vector_utils.c \
				./src/controls/key_controls.c \
				./src/controls/ft_keys.c \
				./src/controls/rotation.c \
				./src/controls/translation.c \
				./src/controls/navigate.c \
				./src/controls/object_select.c \
				./src/controls/handle_signal.c \
				./src/controls/rotation_camera.c

MINIRT_OBJS = $(MINIRT_SRCS:.c=.o)
VPATH = src:lib:lib/libft

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx -O3
	MLX_DIR = ./mlx
	MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm
	MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
else
	INCLUDES = -I/opt/X11/include -Imlx
	MLX_FLAGS = -framework OpenGL -framework AppKit
	MLX_DIR = ./mlx_mac
	MLX_LIB = $(MLX_DIR)/libmlx.a
endif

### LIBFT
LIBFT = libft.a
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/$(LIBFT)
LIBR = $(LIBFT_LIB)
### LIBFT

MAKE_LIBR = make --no-print-directory -C

RM = rm -rf

LB = ar rcs

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

$(NAME): $(MINIRT_OBJS)
		$(CC) $(CFLAGS) $(MINIRT_OBJS) $(MLX_FLAGS) $(MLX_LIB) $(LIBFT_LIB) -o $(NAME)

$(LIBFT_LIB):
	$(MAKE_LIBR) $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE_LIBR) $(MLX_DIR)

clean:
	$(RM) $(MINIRT_OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME) $(MINIRT_OBJS)
	$(MAKE_LIBR) $(LIBFT_DIR) fclean
	$(MAKE_LIBR) $(MLX_DIR) clean

re: fclean all
	clear

.PHONY:	all clean fclean re

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m