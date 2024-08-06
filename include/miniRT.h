#ifndef MINIRT_H
# define MINIRT_H

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
  float  x; // do we need double?
  float  y;
  float  z;
} t_vector;

typedef struct s_amlight
{
    float  amlight_ratio;
    t_colour colour;
} t_amlight;

typedef struct s_camera
{
  t_vector  coord;
  t_vector  orient;
  int  fov;
} t_camera;

typedef struct s_light
{
    t_vector coord;
    float brightness;
    t_colour colour;
}  t_light;

typedef struct s_sp
{
  t_vector  coord;
  float diameter;
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
  float diameter;
  float  height;
  t_colour colour;
  struct s_cy  *next;
} t_cy;

typedef struct s_meta
{
  t_amlight  *amlight;
  t_camera  *camera;
  t_light  *light;
  t_sp  *sp;
  t_pl  *pl;
  t_cy  *cy;
  // void  *mlx_ptr;
} t_meta;


void    fill_camera(t_meta *meta_data, char **argv);
void    fill_ambient(t_meta *meta_data, char **argv);
void    fill_light(t_meta *meta_data, char **argv);
int     pointer_count(char **argv);
void    ft_fill_data(t_meta *meta_data, char **argv);
void    data_init(t_meta *meta_data, char *argv);
void	  map_data(t_meta *data, int argc, char **argv);

void    ft_check_args(int argc, char **argv);
void    check_fd(char *argv);
int	    get_fd(char *argv);
void	  free_pointer(char **s);
int	    ft_strlen_dp(char **s);

t_cy    *create_cy(char **argv);
t_pl    *create_pl(char **argv);
t_sp    *create_sp(char **argv);
#endif