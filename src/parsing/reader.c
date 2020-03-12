/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reader.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 06:03:54 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/11 14:43:50 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>
#include <sys/types.h>

static void		*reader_free(void *item0, void *item1)
{
	free(item0);
	free(item1);
	errors(ERR_MALLOC);
	return (NULL);
}

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

	spec[(int)s[0]](s, b);
}

static t_objs	*reader_ext(char **s)
{
	t_objs		*o;
	int			ret;
	int			fd;

	*s = malloc(sizeof(char) * 4096);
	if (*s == NULL)
		return (errors(ERR_MALLOC));
	fd = open(RTFILE, O_RDONLY);
	ret = read(fd, *s, 4096);
	if (ret < 1)
		return (errors(ERR_IN_RT_FILE));
	o = malloc(sizeof(t_objs) * (obj_cntr(*s) + 1));
	if (o == NULL)
		return (reader_free(s, NULL));
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
	o = reader_ext(&s);
	if (o == NULL)
		return (NULL);
	while (s[i])
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
	free(s);
	return (o);
}
