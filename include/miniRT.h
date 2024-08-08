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

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"

typedef struct s_colour
{
    int  r;
    int  g;
    int  b;
}  t_colour;

typedef struct t_vector
{
  double  x; // do we need double?
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
    struct s_light  *next;
}  t_light;

typedef struct s_sp
{
  t_vector  coord;
  double diameter;
  t_colour  colour;
  struct s_sp  *next;
} t_sp;

typedef struct s_pl
{
  t_vector  coord;
  t_vector  normal;
  t_colour colour;
  struct s_pl  *next;
} t_pl;

typedef struct s_cy
{
  t_vector  coord;
  t_vector  axis;
  double diameter;
  double  height;
  t_colour colour;
  struct s_cy  *next;
} t_cy;

typedef struct s_cn
{
  t_vector  coord;
  t_vector  axis;
  double  angle;
  double  height;
  t_colour colour;
  struct s_cn  *next;
} t_cn;

typedef struct s_meta
{
  t_amlight  *amlight;
  t_camera  *camera;
  t_light  *light;
  t_sp  *sp;
  t_pl  *pl;
  t_cy  *cy;
  t_cn  *cn;
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
t_light    *create_light(t_meta *meta_data, char **argv);
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
#endif
