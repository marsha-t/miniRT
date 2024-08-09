#ifndef MINIRT_H
# define MINIRT_H

# define RST    "\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */

# define SF_SPHERE 1
# define SF_PLANE 2
# define SF_CY_CURVE 3
# define SF_CY_BASE_B 4
# define SF_CY_BASE_T 5
# define SF_CONE_CURVE 6
# define SF_CONE_BASE 7

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <float.h>
# include <stdint.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"
# include "../mlx/mlx.h"

typedef struct s_colour
{
    int  r;
    int  g;
    int  b;
    double r_n;
    double g_n;
    double b_n;
}  t_colour;

typedef struct t_vector
{
  double  x;
  double  y;
  double  z;
} t_vector;

typedef struct s_amlight
{
    double  amlight_ratio;
    t_colour colour;
} t_amlight;

typedef struct s_camera
{
  t_vector  coord;
  t_vector  orient;
  double    fov;
} t_camera;

typedef struct s_light
{
    t_vector coord;
    double brightness;
    t_colour colour;
    struct s_light *next;
}  t_light;

typedef struct s_sp
{
  t_vector  coord;
  double diameter;
  t_colour  colour;
	double radius;
  bool  exclude;
  struct s_sp  *next;
} t_sp;

typedef struct s_pl
{
  t_vector  coord;
  t_vector  normal;
  t_colour colour;
  bool  exclude;
  struct s_pl  *next;
} t_pl;

typedef struct s_cy
{
  t_vector  coord;
  t_vector  axis;
  double diameter;
  double  radius;
  double  height;
  t_colour colour;
  t_vector base_bottom;
	t_vector base_top;
  bool  exclude;
  struct s_cy  *next;
} t_cy;


typedef struct s_cn
{
  t_vector  coord;
  t_vector  axis;
  double  angle;
  double  radius;
  double  height;
  t_vector  base;
  t_colour colour;
  bool  exclude;
  struct s_cn  *next;
} t_cn;

typedef struct s_pixel
{
	t_vector	ray;
	double		t;
	void *obj;
	int			surface;
	t_vector	intersect;
  t_vector  shadow;
  t_colour  final;
	/*	
    or
		int			surface; e.g.,
						sphere/plane/cy curve/cy bottom base/cy top base/cone curve/cone base
		int			nth_obj; e.g., 0 = 1st in linked list
	*/
}				t_pixel;

typedef struct s_meta
{
  t_amlight  *amlight;
  t_camera  *camera;
  t_light  *light;
  t_sp  *sp;
  t_pl  *pl;
  t_cy  *cy;
  t_cn  *cn;
  double		aspect_ratio;
	double		img_width;
	double		img_height;
	t_vector	img_up;
	t_vector	img_right;
	t_vector	img_center;
  t_pixel   pixel;
  void      *mlx_ptr;
	void			*mlx_win;
  bool  amlight_allocated;
  bool  camera_allocated;
  bool  light_allocated;
  bool  sp_allocated;
  bool  pl_allocated;
  bool  cy_allocated;
  bool  cn_allocated;
} t_meta;

void    print_banner();
void    fill_camera(t_meta *meta_data, char **argv);
void    fill_ambient(t_meta *meta_data, char **argv);
t_light    *create_light(t_meta *meta_data, char **argv);
int     pointer_count(char **argv);
void    ft_fill_data(t_meta *meta_data, char *singleline);
void    read_data(t_meta *meta_data, char *argv);
void	  parse_data(t_meta *data, int argc, char **argv);
void    meta_data_init(t_meta *meta_data);

void    ft_check_args(int argc, char **argv);
void    check_fd(char *argv);
int	    get_fd(char *argv);
void	  free_pointer(char **s);
void    free_exit(t_meta *meta_data);
void    free_objects(t_meta *meta_data);
void    free_pointerlist(int num, ...);
int	    ft_strlen_dp(char **s);

void    create_objects(t_meta *meta_data, char **argv);
t_cy    *create_cy(t_meta *meta_data, char **argv);
t_pl    *create_pl(t_meta *meta_data, char **argv);
t_sp    *create_sp(t_meta *meta_data, char **argv);
t_cn    *create_cn(t_meta *meta_data, char **argv);

t_colour    check_colour(t_meta **meta_data, void *temp, char **src, char **argv);
bool        check_colour_val(t_meta *meta_data, char **src, int arg_count, char **argv);
t_vector    check_norm(t_meta **meta_data, void *temp, char **src, char **argv);
bool        check_norm_val(t_meta *meta_data, char **src, int arg_count, char **argv);
t_vector    check_coord(t_meta **meta_data, void *temp, char **src, char **argv);
double      check_double(t_meta **meta_data, void *temp, char **src, char *str);
int         check_int(t_meta **meta_data, char *str);

void        print_cylinders(t_meta *meta_data);
void        print_spheres(t_meta *meta_data);
void        print_planes(t_meta *meta_data);
void        print_cones(t_meta *meta_data);
void        print_light(t_meta *meta_data);

// Prepare derived parameters: prepare.c
void	prepare_data(t_meta *meta_data);
void	prepare_img(t_meta *meta_data);
void	img_basis_vec(t_meta *meta_data);
void	prepare_light(t_meta *meta_data);
void	prepare_obj(t_meta *meta_data);
void	prepare_sp(t_sp *start);
void	prepare_pl(t_pl *start);
void	prepare_cy(t_cy *start);
void	prepare_cn(t_cn *start);

// Prepare image: img.c
void	gen_img(t_meta *meta_data);
void	init_pixel(t_pixel *pixel);
void  ray_dir(int i, int j, t_meta *meta_data);

// Calculate closest intersection: intersect.c
void	intersect_closest(t_meta *meta_data);
void	intersect_sp(t_meta *meta_data, t_sp *sphere);
void	intersect_pl(t_meta *meta_data, t_pl *plane);
void	intersect_cy(t_meta *meta_data, t_cy *cylinder);
void	intersect_cy_curve(t_meta *meta_data, t_cy *cylinder);
void	update_t_cy_curve(t_meta *meta_data, t_cy *cylinder, double t);
void	intersect_cy_base(t_meta *meta_data, t_cy *cylinder);
void	intersect_cn(t_meta *meta_data, t_cn *cone);
void	intersect_cn_curve(t_meta *meta_data, t_cn *cone);
void	update_t_cn_curve(t_meta *meta_data, t_cn *cone, double t);
void	intersect_cn_base(t_meta *meta_data, t_cn *cone);
void	get_ray_pt(t_vector *dest, t_meta *meta_data, double t);

// Calculate final colour at intersection: final_colour.c
void	gen_final_colour(t_meta *meta_data);
void	get_ambient(t_meta *meta_data);

// Vector operations: vector_op.c
double	vec_dot_product(t_vector *a, t_vector *b);
double	vec_len(t_vector *vec);
void	vec_subtract(t_vector *dest, t_vector *a, t_vector *b);
void	vec_add(t_vector *dest, t_vector *a, t_vector *b);
void  vec_multiply_scalar(t_vector *dest, t_vector *vec, double n);
void	vec_normalise(t_vector *vec);
void	vec_cross_product(t_vector *dest, t_vector *a, t_vector *b);

// Vector utility functions: vector_utils.c
void	print_vector(char *str, t_vector *vec);
int	vec_cmp_num(t_vector *vec, double x, double y, double z);

// Miscellaneous math functions: misc_math.c
double	deg_to_rad(int degree);

#endif
