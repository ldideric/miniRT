/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/30 10:28:36 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/06 12:15:59 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <libft.h>
# include <mlx.h>

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

/*
** DEFINES ---------------------------------------------------- |
*/

# ifndef RTFILE
#  define RTFILE "mini.rt"
# endif

# define WIN_NAME "bepis is better than pepsi"
# define TRUE	1
# define FALSE	0

/*
** ERROR MESSAGES
*/

# define ERR_IN_RT_FILE		10
# define ERR_MALLOC			11
# define ERR_02				12
# define ERR_03				13

/*
** STRUCTS ---------------------------------------------------- |
*/

typedef struct		s_res
{
	int				x_max;
	int				y_max;
}					t_res;

typedef struct		s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_rgb;

typedef struct		s_vect
{
	double			x;
	double			y;
	double			z;
}					t_vect;

typedef struct		s_light
{
	t_vect			pos;
	t_rgb			rgb;
	double			bright;
}					t_light;

typedef struct		s_cam
{
	t_vect			pos;
	t_vect			vec;
	int				fov;
}					t_cam;

typedef struct		s_amb
{
	double			amb;
	t_rgb			rgb;
}					t_amb;

/*
** all basic input from mini.rt file
*/
typedef struct		s_base
{
	t_res			res;
	t_amb			amb;
	t_cam			cam;
	t_light			light;
}					t_base;

/*
** A struct for any kind of object.
*/
typedef struct		s_objs
{
	char			type;
	t_vect			pos1;
	t_vect			pos2;
	t_vect			pos3;
	t_vect			vec;
	double			dia;
	double			height;
	double			size;
	t_rgb			rgb;
}					t_objs;

/*
** | ----------------------------------------------------------------------- |
*/

typedef struct		s_vars
{
	void			*mlx;
	void			*win;
}					t_vars;

typedef struct		s_data
{
	void			*img;
	char			*addr;
	int				bpp;
	int				len;
	int				endian;
}					t_data;

/*
** | ----------------------------------------------------------------------- |
*/

typedef void		(*t_spec_b)(char *s, t_base *b);
typedef void		(*t_spec_o)(char *s, t_objs *o);

void				printer(t_objs *o);

void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_vect				ft_normalize(t_vect p);
void				graphing(t_data *img, int x_max, int y_max);
void				hooks(t_vars *vars);
int					obj_cntr(char *s);
void				*errors(int error);

void				raytracer(t_data *img, t_base b, t_objs *o);
t_vect				calc_vect(t_vect start, t_vect end);
t_vect				get_px_pos(t_base *b, int x, int y);

t_objs				*reader(t_base *t);
char				*rd_vect(char *s, t_vect *vect);
char				*rd_rgb(char *s, t_rgb *rgb);

void				rd_res(char *s, t_base *t);
void				rd_amb(char *s, t_base *t);
void				rd_cam(char *s, t_base *t);
void				rd_light(char *s, t_base *t);

void				rd_sphere(char *s, t_objs *o);
void				rd_plane(char *s, t_objs *o);
void				rd_square(char *s, t_objs *o);
void				rd_cylinder(char *s, t_objs *o);
void				rd_triangle(char *s, t_objs *o);

#endif
