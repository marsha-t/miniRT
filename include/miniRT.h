/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaravil <emaravil@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:04:13 by emaravil          #+#    #+#             */
/*   Updated: 2024/09/25 17:43:38 by emaravil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define RST "\033[0m"    /* Reset to default color */
# define RED "\033[1;31m" /* Bold Red */
# define G "\033[1;32m"   /* Bold Green */
# define Y "\033[1;33m"   /* Bold Yellow */
# define B "\033[1;34m"   /* Bold Blue */
# define M "\033[1;35m"   /* Bold Magenta */
# define C "\033[1;36m"   /* Bold Cyan */
# define W "\033[1;37m"   /* Bold White */

# define SF_SPHERE 1
# define SF_PLANE 2
# define SF_CY_CURVE 3
# define SF_CY_BASE_B 4
# define SF_CY_BASE_T 5
# define SF_CONE_CURVE 6
# define SF_CONE_BASE 7
# define SQSIZE_FLAT 5

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 800
# define FOCAL_LENGTH 0.5
# define LOW_RES 45
# define MID_RES 22
# define HIGH_RES 5

# define KEY_ESC 53
# define NUMPAD_0 82
# define NUMPAD_1 83
# define NUMPAD_2 84
# define NUMPAD_3 85
# define NUMPAD_4 86
# define NUMPAD_5 87
# define NUMPAD_6 88
# define NUMPAD_7 89
# define NUMPAD_8 91
# define NUMPAD_9 92
# define NUMPAD_PLUS 69
# define NUMPAD_MIN 78
# define ARROW_LEFT 126
# define ARROW_UP 123
# define ARROW_DOWN 125
# define ARROW_RIGHT 124
# define KEY_Q 12
# define KEY_A 0
# define KEY_W 13
# define KEY_S 1
# define KEY_E 14
# define KEY_D 2
# define KEY_R 15
# define KEY_U 32
# define KEY_J 38
# define KEY_I 34
# define KEY_K 40
# define KEY_O 31
# define KEY_L 37
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_5 23
# define KEY_6 22
# define KEY_7 26
# define DBL_MAX 1.7976931348623158e+308
# define INTENSITY_SCALE 5

// # define NUMPAD_0 65438
// # define NUMPAD_1 65436
// # define NUMPAD_2 65433
// # define NUMPAD_3 65435
// # define NUMPAD_4 65430
// # define NUMPAD_5 65437
// # define NUMPAD_6 65432
// # define NUMPAD_7 65429
// # define NUMPAD_8 65431
// # define NUMPAD_9 65434
// # define ARROW_LEFT 65361
// # define ARROW_UP 65362
// # define ARROW_DOWN 65364
// # define ARROW_RIGHT 65363
// # define KEY_Q 113
// # define KEY_A 97
// # define KEY_W 119
// # define KEY_S 115
// # define KEY_E 101
// # define KEY_D 100

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// # include <float.h>
# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "../mlx_mac/mlx.h"
# include <stdint.h>

typedef struct s_img
{
	void				*img;
	int					width;
	int					height;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_img;

typedef struct s_sqsize
{
	double				row;
	double				col;
}						t_sqsize;

typedef struct s_colour
{
	double				r;
	double				g;
	double				b;
	double				r_n;
	double				g_n;
	double				b_n;
}						t_colour;

typedef struct t_vector
{
	double				x;
	double				y;
	double				z;
}						t_vector;

typedef struct s_amlight
{
	double				amlight_ratio;
	t_colour			colour;
}						t_amlight;

typedef struct s_camera
{
	t_vector			coord;
	t_vector			orient;
	double				fov;
}						t_camera;

typedef struct s_spotlight
{
	t_vector			coord;
	double				brightness;
	t_colour			colour;
	t_vector			spot_dir;
	double				*spot_theta;
	struct s_spotlight	*next;
}						t_spotlight;

typedef struct s_light
{
	t_vector			coord;
	double				brightness;
	t_colour			colour;
	struct s_light		*next;
}						t_light;

typedef struct s_sp
{
	t_vector			coord;
	double				diameter;
	t_colour			colour;
	double				radius;
	bool				checker;
	t_sqsize			sqsize;
	bool				bump;
	t_img				bump_img;
	struct s_sp			*next;
}						t_sp;

typedef struct s_pl
{
	t_vector			coord;
	t_vector			normal;
	t_colour			colour;
	bool				checker;
	t_sqsize			sqsize;
	bool				bump;
	t_img				bump_img;
	struct s_pl			*next;
}						t_pl;

typedef struct s_cy
{
	t_vector			coord;
	t_vector			axis;
	double				diameter;
	double				radius;
	double				height;
	t_colour			colour;
	t_vector			base_bottom;
	t_vector			base_top;
	bool				checker;
	t_sqsize			sqsize;
	bool				bump;
	t_img				bump_img;
	struct s_cy			*next;
}						t_cy;

typedef struct s_cn
{
	t_vector			coord;
	t_vector			axis;
	double				angle;
	double				radius;
	double				height;
	t_vector			base;
	t_colour			colour;
	bool				checker;
	t_sqsize			sqsize;
	struct s_cn			*next;
}						t_cn;

typedef struct s_pixel
{
	t_vector			ray;
	double				t;
	double				coeff_ref;
	double				shine_fac;
	double				spot_attenuate;
	double				spot_intensity;
	double				spot_theta;
	double				spot_p;
	double				spot_k0;
	double				spot_k1;
	double				spot_k2;
	void				*obj;
	int					surface;
	t_vector			intersect;
	t_vector			shadow;
	t_vector			shadow_spot;
	t_vector			coord;
	t_colour			final;
	t_vector			normal;
	double				theta_x;
	double				theta_y;
	double				theta_z;
}						t_pixel;

typedef struct s_objoption
{
	t_vector			*coord;
	t_colour			*colour;
	double				*size;
}						t_objoption;

typedef struct s_meta
{
	t_amlight			*amlight;
	t_camera			*camera;
	t_light				*light;
	t_spotlight			*spotlight;
	t_sp				*sp;
	t_pl				*pl;
	t_cy				*cy;
	t_cn				*cn;
	int					obj_select;
	t_objoption			*obj_option;
	void				*obj;
	double				aspect_ratio;
	double				img_width;
	double				img_height;
	t_vector			img_up;
	t_vector			img_right;
	t_vector			img_center;
	t_pixel				pixel;
	int					row;
	int					col;
	void				*mlx_ptr;
	void				*mlx_win;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	bool				amlight_allocated;
	bool				camera_allocated;
	bool				light_allocated;
	bool				sl_allocated;
	bool				sp_allocated;
	bool				pl_allocated;
	bool				cy_allocated;
	bool				cn_allocated;
	bool				move;
	bool				rotate;
	bool				move_x_d;
	bool				move_x_i;
	bool				move_y_d;
	bool				move_y_i;
	bool				move_z_d;
	bool				move_z_i;
	bool				rot_x_d;
	bool				rot_x_i;
	bool				rot_y_d;
	bool				rot_y_i;
	bool				rot_z_d;
	bool				rot_z_i;
	bool				rot_reset;
	t_colour			q1;
	t_colour			q2;
	t_colour			q3;
	t_colour			q4;
	int					x;
	int					y;
	int					a1;
	int					a2;
	int					b1;
	int					b2;
	t_vector			orient;
	struct s_colour		prev_arr[WINDOW_WIDTH + 1];
	struct s_colour		curr_arr[WINDOW_WIDTH + 1];
	bool				low_quality;
	bool				mid_quality;
	int					step_y;
	int					step_x;
	t_colour			colour_init;
}						t_meta;

void					rt_mlxinit(t_meta *meta_data);
void					draw(t_meta *meta_data);
int						handle_keyrelease(int key, void *param);
int						handle_keypress(int key, void *param);
int						update(t_meta *meta_data);
void					print_banner(void);
void					fill_camera(t_meta *meta_data, char **argv);
void					fill_camera_args(t_meta *meta_data, int count,
							char **argv);
void					fill_ambient(t_meta *meta_data, char **argv);
void					fill_exit(t_meta *meta_data, char **argv);
t_light					*create_light(t_meta *meta_data, char **argv);
int						pointer_count(char **argv);
void					ft_fill_data(t_meta *meta_data, char *singleline);
void					ft_fill_light(t_meta *meta_data, char **argv);
void					ft_fill_spotlight(t_meta *meta_data, char **argv);
void					ft_fill_objects(t_meta *meta_data, char **argv);
void					read_data(t_meta *meta_data, char *argv);
void					parse_data(t_meta *data, int argc, char **argv);
void					clean_data(t_meta *meta_data, char *singleline,
							int index);
void					meta_data_init(t_meta *meta_data);
void					meta_data_init_a(t_meta *meta_data);
void					translate_camera(t_meta *meta_data);
void					translate_camera_a(t_meta *meta_data);
void					translate_camera_b(t_meta *meta_data);
void					translate_light(t_vector *vector, int key);
void					translate_spotlight(t_vector *vector, int key);
void					ft_check_args(int argc, char **argv);
void					check_fd(char *argv);
int						get_fd(char *argv);
void					free_pointer(char **s);
void					free_exit(t_meta *meta_data);
void					free_objects(t_meta *meta_data);
void					free_spheres(t_meta *meta_data);
void					free_planes(t_meta *meta_data);
void					free_cylinders(t_meta *meta_data);
void					free_cones(t_meta *meta_data);
void					free_args(t_meta *meta_data, char **argv);
void					free_pointerlist(int num, ...);
int						ft_strlen_dp(char **s);
void					create_objects(t_meta *meta_data, char **argv);
void					init_cylinder(t_meta *meta_data, char **argv);
void					init_plane(t_meta *meta_data, char **argv);
void					init_sphere(t_meta *meta_data, char **argv);
void					init_cone(t_meta *meta_data, char **argv);
t_light					*create_light(t_meta *meta_data, char **argv);
t_light					*check_light_args(t_meta *meta_data, char **argv);
t_spotlight				*create_spotlight(t_meta *meta_data, char **argv);
t_spotlight				*check_spotlight_args(t_meta *meta_data, char **argv);
t_cy					*create_cy(t_meta *meta_data, char **argv);
t_cy					*check_cy_args(t_meta *meta_data, char **argv);
void					cy_bonus(t_meta *meta_data, t_cy *cy, char **argv);
void					cy_elements(t_meta *meta_data, t_cy *cy, char **argv);
void					cylinder_exit(t_meta *meta_data, char **argv,
							char *message);
t_pl					*create_pl(t_meta *meta_data, char **argv);
t_pl					*check_pl_args(t_meta *meta_data, char **argv);
void					pl_elements(t_meta *meta_data, t_pl *pl, char **argv);
t_sp					*create_sp(t_meta *meta_data, char **argv);
void					sp_bonus(t_meta *meta_data, t_sp *sp, char **argv);
void					sp_elements(t_meta *meta_data, t_sp *sp, char **argv);
t_sp					*check_sp_args(t_meta *meta_data, char **argv);
t_cn					*create_cn(t_meta *meta_data, char **argv);
t_cn					*check_cn_args(t_meta *meta_data, char **argv);
void					cn_bonus(t_meta *meta_data, t_cn *cn, char **argv);
void					cn_elements(t_meta *meta_data, t_cn *cn, char **argv);
void					cone_exit(t_meta *meta_data, char **argv);
t_colour				check_colour(t_meta **meta_data, void *temp, char **src,
							char **argv);
bool					check_colour_val(t_meta *meta_data, char **src,
							int arg_count, char **argv);
void					colour_exit(t_meta **meta_data, void *temp, char **src,
							char **argv);
t_vector				check_norm(t_meta **meta_data, void *temp, char **src,
							char **argv);
void					norm_exit(t_meta **meta_data, void *temp, char **src,
							char **argv);
bool					check_norm_val(t_meta *meta_data, char **src,
							int arg_count, char **argv);
t_vector				check_coord(t_meta **meta_data, void *temp, char **src,
							char **argv);
void					coord_exit(t_meta **meta_data, void *temp, char **src,
							char **argv);
double					check_double(t_meta **meta_data, void *temp, char **src,
							char *str);
int						check_int(t_meta **meta_data, char *str);
t_sqsize				check_checker(t_meta **meta_data, void *temp,
							char **src, char **argv);
void					checker_exit(t_meta **meta_data, void *temp, char **src,
							char **argv);
t_img					check_bump(t_meta **meta_data, void *temp, char **src,
							char **argv);
void					bump_exit(t_meta **meta_data, void *temp, char **src,
							char **argv);
bool					is_xpm_file(char *path);
void					print_cylinders(t_meta *meta_data);
void					print_spheres(t_meta *meta_data);
void					print_planes(t_meta *meta_data);
void					print_cones(t_meta *meta_data);
void					print_light(t_meta *meta_data);
void					print_spotlight(t_meta *meta_data);
int						ft_key(int key, void *param);
int						ft_close(t_meta *meta_data);
void					ft_objectselect(t_meta *meta_data, int key);
void					object_select_a(t_meta *meta_data, int key);
void					object_select_b(t_meta *meta_data, int key);
void					ft_controls(t_meta *meta_data);
void					ft_controls_status(t_meta *meta_data, int key,
							bool status);
void					navigate_cycn(t_meta *meta_data, int key);
void					navigate_light(t_meta *meta_data, int key);
void					navigate_sppl(t_meta *meta_data, int key);
void					increase_size(t_meta *meta_data, int key);
void					rotate_camera_z(t_vector *orientation, double theta_x);
void					rotate_camera_x(t_vector *orientation, double theta_x);
void					rotate_camera_y(t_vector *orientation, double theta_y);
void					ft_rotation_status(t_meta *meta_data, int key,
							bool status);
void					map_draw(t_meta *meta_data);
void					img_mlx_pixel_put(t_meta *meta_data, int x, int y,
							int color);
int						create_trgb(int r, int g, int b);

// Prepare derived parameters: prepare1.c
void					prepare_data(t_meta *meta_data);
void					prepare_img(t_meta *meta_data);
void					img_basis_vec(t_meta *meta_data);
void					prepare_light(t_meta *meta_data);

// Prepare derived parameters: prepare2.c
void					prepare_obj(t_meta *meta_data);
void					prepare_sp(t_sp *start);
void					prepare_pl(t_pl *start);
void					prepare_cy(t_cy *start);
void					prepare_cn(t_cn *start);

// Prepare image: img.c
void					gen_img(t_meta *meta_data);
void					init_pixel(t_pixel *pixel);
void					ray_dir(int i, int j, t_meta *meta_data);
double					color_diff(t_colour prev, t_colour curr);
void					render(t_meta *meta_data, int x, int y);
void					render_image(t_meta *meta_data, int x, int y);
void					render_y(t_meta *meta_data, int x, int y);
void					render_x(t_meta *meta_data, int x, int y);
void					interpolate_x(t_meta *meta_data, t_colour prev, int x,
							int y);
void					interpolate_y(t_meta *meta_data, t_colour prev, int x,
							int y);
void					bilinear_interpolation(t_meta *meta_data, int x, int y);

// Calculate closest intersection for ray direction: intersect.c
void					intersect_closest(t_meta *meta_data);
void					intersect_closest_sp_pl(t_meta *meta_data);
void					intersect_closest_cy_cn(t_meta *meta_data);

void					intersect_sp(t_meta *meta_data, t_sp *sphere,
							t_vector *ray);
void					intersect_pl(t_meta *meta_data, t_pl *plane,
							t_vector *ray);
void					intersect_cy(t_meta *meta_data, t_cy *cylinder,
							t_vector *ray);
void					intersect_cn(t_meta *meta_data, t_cn *cone,
							t_vector *ray);

// Calculate intersection between any given ray and object: intersect_math1.c
double					intersect_sp_math(t_sp *sphere, t_vector *ray,
							t_vector *origin);
double					intersect_pl_math(t_pl *plane, t_vector *ray,
							t_vector *origin);
double					intersect_cy_curve_math(t_cy *cylinder, t_vector *ray,
							t_vector *origin);
double					intersect_cy_curveval(t_meta *meta_data,
							t_vector *new_origin, t_cy *cylinder, bool check);
double					intersect_cy_base_math(t_cy *cylinder, int base,
							t_vector *ray, t_vector *origin);
double					cy_curve_check(t_cy *cy, double t, t_vector *ray,
							t_vector *origin);

// Calculate intersection between any given ray and object: intersect_math2.c
double					intersect_cn_curve_math(t_cn *cone, t_vector *ray,
							t_vector *origin);
double					intersect_cn_base_math(t_cn *cone, t_vector *ray,
							t_vector *origin);

// Calculate derived data of intersection: intersect_prepare.c
void					prepare_intersect(t_pixel *pixel);
void					prepare_intersect_sp(t_pixel *pixel);
void					prepare_intersect_pl(t_pixel *pixel);
void					prepare_intersect_cy(t_pixel *pixel);
void					prepare_intersect_cn(t_pixel *pixel);

// Calculate normal at intersection point: get_normal.c
t_vector				get_sp_normal(t_vector surface_point, t_vector center);
t_vector				get_cy_curve_normal(t_pixel *pixel, t_cy *cylinder);
t_vector				get_cn_curve_normal(t_pixel *pixel, t_cn *cone);

// Utility functions needed for intersection calculation: intersect_utils.c
double					quadratic_formula(double a, double b, double c);
void					get_ray_pt(t_vector *dest, t_vector *ray,
							t_vector *origin, double t);

// Calculate final colour at intersection: final_colour.c
void					gen_final_colour(t_meta *meta_data);
void					init_final_colour(t_meta *meta_data, t_colour *diffuse,
							t_colour *specular, t_colour *ambient);
void					gen_final_colour_light(t_meta *meta_data,
							t_colour *diffuse, t_colour *specular);
void					gen_final_colour_spotlight(t_meta *meta_data,
							t_colour *diffuse, t_colour *specular);
t_vector				calculate_light_direction(t_vector surface_point,
							t_vector light_position);

// Calculate diffuse and specular colour components: diffuse_specular.c
void					gen_diffuse(t_meta *meta_data, t_light *curr,
							t_colour *diffuse);
void					gen_specular(t_meta *meta_data, t_light *curr,
							t_colour *specular);
void					gen_diffuse_spotlight(t_meta *meta_data,
							t_spotlight *curr_sl, t_colour *diffuse);
void					gen_specular_spotlight(t_meta *meta_data,
							t_spotlight *curr_sl, t_colour *specular);

// Calculate shadow: shadow.c
bool					in_shadow(t_meta *meta_data, t_light *light);
bool					in_shadow_spotlight(t_meta *meta_data,
							t_spotlight *spotlight);
bool					in_shadow_spotlight_setup(t_meta *meta_data,
							t_spotlight *spotlight, double *len,
							t_vector *new_origin);

// Calculate shadow for each object: shadow_obj.c
bool					in_shadow_sp(t_meta *meta_data, t_vector *new_origin,
							double len, bool check);
bool					in_shadow_pl(t_meta *meta_data, t_vector *new_origin,
							double len, bool check);
bool					in_shadow_cy(t_meta *meta_data, t_vector *new_origin,
							double len, bool check);
bool					in_shadow_cn(t_meta *meta_data, t_vector *new_origin,
							double len, bool check);

// Get UV coordinates: uv_map1.c
void					uv_map_pl(t_pixel *pixel, t_pl *plane, double *u,
							double *v);
void					uv_map_sp(t_pixel *pixel, t_sp *sphere, double *u,
							double *v);
void					uv_map_cy_curve(t_pixel *pixel, t_cy *cylinder,
							double *u, double *v);
void					uv_map_cy_base(t_pixel *pixel, t_cy *cylinder,
							double *u, double *v);

// Get UV coordinates: uv_map2.c
void					uv_map_cn_curve(t_pixel *pixel, t_cn *cone, double *u,
							double *v);
void					uv_map_cn_base(t_pixel *pixel, t_cn *cone, double *u,
							double *v);

// Apply checkerboard pattern: checkerboard1.c
void					get_checkerboard(t_meta *meta_data);
void					get_checkerboard_pl(t_meta *meta_data, t_pl *plane);
void					get_checkerboard_sp(t_meta *meta_data, t_sp *sphere);
void					get_checkerboard_cy_curve(t_meta *meta_data,
							t_cy *cylinder);
void					get_checkerboard_cy_base(t_meta *meta_data,
							t_cy *cylinder);

// Apply checkerboard pattern: checkerboard2.c
void					get_checkerboard_cn_curve(t_meta *meta_data,
							t_cn *cone);
void					get_checkerboard_cn_base(t_meta *meta_data, t_cn *cone);
void					least_parallel_avector(t_vector *a, t_vector *normal);
void					assign_checker_colour(int row, int column,
							t_colour *colour);

// Apply bump map textures: bumpmap.c
t_vector				get_sp_bm_normal(t_pixel *pixel, t_sp *sphere);
t_vector				get_pl_bm_normal(t_pixel *pixel, t_pl *plane);
t_vector				get_cy_curve_bm_normal(t_pixel *pixel, t_cy *cylinder);
t_vector				get_cy_base_bm_normal(t_pixel *pixel, t_cy *cylinder);
t_vector				get_cn_curve_bm_normal(t_pixel *pixel, t_cn *cone);
t_vector				get_cn_base_bm_normal(t_pixel *pixel, t_cn *cone);

// Apply bump map textures (utility functions): bumpmap_utils.c
void					get_bm_gradient(t_img *img, double *u, double *v);
t_vector				perturb_normal(t_vector *ori_normal, double u,
							double v);

// Vector operations: vector_op1.c
double					vec_dot_product(t_vector *a, t_vector *b);
void					vec_inv(t_vector *dest, t_vector *a);
double					vec_len(t_vector *vec);
void					vec_subtract(t_vector *dest, t_vector *a, t_vector *b);
void					vec_add(t_vector *dest, t_vector *a, t_vector *b);

// Vector operations: vector_op2.c
void					vec_multiply_scalar(t_vector *dest, t_vector *vec,
							double n);
void					vec_normalise(t_vector *vec);
void					vec_cross_product(t_vector *dest, t_vector *a,
							t_vector *b);

// Vector utility functions: vector_utils.c
void					print_vector(char *str, t_vector *vec);
int						vec_cmp_num(t_vector *vec, double x, double y,
							double z);

// Miscellaneous math functions: misc_math.c
double					deg_to_rad(int degree);

#endif
