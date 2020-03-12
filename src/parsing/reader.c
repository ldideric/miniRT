/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reader.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 06:03:54 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/12 15:53:44 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>
#include <sys/types.h>

static void		o_specifier(char *s, t_objs *o)
{
	static const t_read_o spec[128] = {
		['1'] = &rd_sphere,
		['2'] = &rd_plane,
		['3'] = &rd_square,
		['4'] = &rd_cylinder,
		['5'] = &rd_triangle,
	};

	(*(u_int16_t *)s == *(u_int16_t *)"sp") ? spec['1'](s, o) : NULL;
	(*(u_int16_t *)s == *(u_int16_t *)"pl") ? spec['2'](s, o) : NULL;
	(*(u_int16_t *)s == *(u_int16_t *)"sq") ? spec['3'](s, o) : NULL;
	(*(u_int16_t *)s == *(u_int16_t *)"cy") ? spec['4'](s, o) : NULL;
	(*(u_int16_t *)s == *(u_int16_t *)"tr") ? spec['5'](s, o) : NULL;
}

static void		b_specifier(char *s, t_base *b)
{
	static const t_read_b spec[128] = {
		['R'] = &rd_res,
		['A'] = &rd_amb,
		['c'] = &rd_cam,
		['l'] = &rd_light,
	};

	if (s[0] == 'c')
	{
		b->i_c++;
		b->cam.max = b->i_c + 1;
	}
	if (s[0] == 'l')
		b->i_l++;
	spec[(int)s[0]](s, b);
}

static t_objs	*reader_ext(char **s, t_base *t)
{
	t_objs		*o;
	int			ret;
	int			fd;

	s[0] = malloc(sizeof(char) * (4096 + 1));
	if (s[0] == NULL)
		return (errors(ERR_MALLOC));
	fd = open(t->file, O_RDONLY);
	ret = read(fd, s[0], 4096);
	if (ret < 1)
		return (errors(ERR_IN_RT_FILE));
	s[0][ret] = '\0';
	o = malloc(sizeof(t_objs) * (obj_cntr(s[0]) + 1));
	if (o == NULL)
		return (reader_free(s, NULL, NULL, NULL));
	t->cam.c = malloc(sizeof(t_cam) * (cam_light_cntr(s[0], 'c') + 1));
	if (t->cam.c == NULL)
		return (reader_free(s, o, NULL, NULL));
	t->i_c = -1;
	t->light = malloc(sizeof(t_light) * (cam_light_cntr(s[0], 'l') + 1));
	if (t->light == NULL)
		return (reader_free(s, o, t->cam.c, NULL));
	t->i_l = -1;
	return (o);
}

t_objs			*reader(t_base *t)
{
	t_objs		*o;
	char		*s;
	int			i;
	int			c_objs;

	i = 0;
	c_objs = 0;
	o = reader_ext(&s, t);
	if (o == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (ft_isalpha(s[i]) && ft_isalpha(s[i + 1]))
		{
			o_specifier(s + i, &o[c_objs]);
			c_objs++;
			i++;
		}
		else if (ft_isalpha(s[i]))
			b_specifier(s + i, t);
		i++;
	}
	o[c_objs].type = 0;
	t->i_c = 0;
	free(s);
	return (o);
}
