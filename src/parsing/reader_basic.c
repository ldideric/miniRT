/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reader_basic.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 07:02:56 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/10 18:56:45 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

char			*rd_rgb(char *s, t_rgb *rgb)
{
	rgb->packed.r = (unsigned char)ft_atoi(s);
	while (*s != ',')
		s++;
	s++;
	rgb->packed.g = (unsigned char)ft_atoi(s);
	while (*s != ',')
		s++;
	s++;
	rgb->packed.b = (unsigned char)ft_atoi(s);
	while (ft_isdigit(*s) || *s == '.')
		s++;
	return (s);
}

char			*rd_vect(char *s, t_vect *vect)
{
	vect->x = ft_atof(s);
	while (*s != ',')
		s++;
	s++;
	vect->y = ft_atof(s);
	while (*s != ',')
		s++;
	s++;
	vect->z = ft_atof(s);
	while (ft_isdigit(*s) || *s == '.')
		s++;
	return (s);
}

void			rd_res(char *s, t_base *t)
{
	s++;
	while (*s == ' ' || *s == '\t')
		s++;
	t->res.x_max = ft_atoi(s);
	while (ft_isdigit(*s))
		s++;
	s++;
	t->res.y_max = ft_atoi(s);
}

void			rd_amb(char *s, t_base *t)
{
	s++;
	while (*s == ' ' || *s == '\t')
		s++;
	t->amb.amb = ft_atof(s);
	while (ft_isdigit(*s) || *s == '.')
		s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_rgb(s, &t->amb.rgb);
}

void			rd_cam(char *s, t_base *t)
{
	s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_vect(s, &t->cam.pos);
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_vect(s, &t->cam.vec);
	while (*s == ' ' || *s == '\t')
		s++;
	t->cam.fov = ft_atoi(s);
}

void			rd_light(char *s, t_base *t)
{
	s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_vect(s, &t->light.pos);
	while (*s == ' ' || *s == '\t')
		s++;
	t->light.bright = ft_atof(s);
	while (ft_isdigit(*s) || *s == '.')
		s++;
	while (*s == ' ' || *s == '\t')
		s++;
	s = rd_rgb(s, &t->light.rgb);
}
