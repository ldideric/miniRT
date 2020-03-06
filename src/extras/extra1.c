/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:23:37 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/06 12:12:08 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char		*dst;

	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int			obj_cntr(char *s)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (ft_isalpha(s[i]) && ft_isalpha(s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

t_vect		ft_normalize(t_vect p)
{
	double w;

	w = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
	p.x /= w;
	p.y /= w;
	p.z /= w;
	return (p);
}

void		printer(t_objs *o)
{
	int i;

	i = 0;
	while (o[i].type && o[i].type != 0)
	{
		if (o[i].type == 's')
			printf("sp\t%f,%f,%f\t\t\t\t\t\t\t%f\t\t\t\t%d,%d,%d\n",
			o[i].pos1.x, o[i].pos1.y, o[i].pos1.z, o[i].dia, o[i].rgb.r,
			o[i].rgb.g, o[i].rgb.b);
		else if (o[i].type == 'p')
			printf("pl\t%f,%f,%f\t\t%f,%f,%f\t\t\t\t\t\t\t%d,%d,%d\n",
			o[i].pos1.x, o[i].pos1.y, o[i].pos1.z, o[i].vec.x, o[i].vec.y,
			o[i].vec.z, o[i].rgb.r, o[i].rgb.g, o[i].rgb.b);
		else if (o[i].type == 'q')
			printf("sq\t%f,%f,%f\t\t%f,%f,%f\t\t%f\t\t\t\t%d,%d,%d\n",
			o[i].pos1.x, o[i].pos1.y, o[i].pos1.z, o[i].vec.x, o[i].vec.y,
			o[i].vec.z, o[i].size, o[i].rgb.r, o[i].rgb.g, o[i].rgb.b);
		else if (o[i].type == 'c')
			printf("cy\t%f,%f,%f\t\t%f,%f,%f\t\t%f\t\t%f\t%d,%d,%d\n",
			o[i].pos1.x, o[i].pos1.y, o[i].pos1.z, o[i].vec.x, o[i].vec.y,
			o[i].vec.z, o[i].dia, o[i].height, o[i].rgb.r, o[i].rgb.g,
			o[i].rgb.b);
		else if (o[i].type == 't')
			printf("tr\t%f,%f,%f\t\t%f,%f,%f\t\t%f,%f,%f\t\t%d,%d,%d\n",
			o[i].pos1.x, o[i].pos1.y, o[i].pos1.z, o[i].pos2.x, o[i].pos2.y,
			o[i].pos2.z, o[i].pos3.x, o[i].pos3.y, o[i].pos3.z, o[i].rgb.r,
			o[i].rgb.g, o[i].rgb.b);
		i++;
	}
}
