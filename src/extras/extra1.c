/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:23:37 by ldideric      #+#    #+#                 */
/*   Updated: 2020/06/29 15:08:32 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char		*dst;

	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void		*reader_free(void *a, void *b, void *c, void *d)
{
	free(a);
	free(b);
	free(c);
	free(d);
	return (errors(ERR_MALLOC));
}

int			cam_light_cntr(char *s, char c)
{
	int count;
	int i;

	i = 0;
	count = 0;
	if (s[i] == c && !ft_isalpha(s[i + 1]))
		count++;
	i++;
	while (s[i] != '\0' && s[i + 1] != '\0')
	{
		if (!ft_isalpha(s[i - 1]) && s[i] == c && !ft_isalpha(s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

int			obj_cntr(char *s)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i] != '\0' && s[i + 1] != '\0')
	{
		if (s[i] == '#')
			while ((s[i] != '\n' && s[i + 1] != '\n')
				|| (s[i] != '\0' && s[i + 1] != '\0'))
				i++;
		if (ft_isalpha(s[i]) && ft_isalpha(s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

void		norm_cam_printer(t_data *data)
{
	int		i;

	i = data->b.i_c;
	ft_printf("\x1b[38;5;83m[+]\x1b[0mCam: %02d/%02d\n", i + 1,
	data->b.cam.max);
	ft_printf("\x1b[38;5;83m[+]\x1b[0mpos:%d,%d,%d - vec:%d,%d,%d - \
	fov:%d\n---\n", (int)data->b.cam.c[i].pos.x, (int)data->b.cam.c[i].pos.y,
	(int)data->b.cam.c[i].pos.z, (int)data->b.cam.c[i].vec.x,
	(int)data->b.cam.c[i].vec.y, (int)data->b.cam.c[i].vec.z,
	(int)data->b.cam.c[i].fov);
}

void		printer(t_objs *o)
{
	int i;

	i = 0;
	while (o[i].type && o[i].type != 0)
	{
		if (o[i].type == 's')
			ft_printf("sp\t%f,%f,%f\t\t\t\t\t\t\t%f\t\t\t\t%d,%d,%d\n",
			o[i].pos1.x, o[i].pos1.y, o[i].pos1.z, o[i].dia, o[i].rgb.packed.r,
			o[i].rgb.packed.g, o[i].rgb.packed.b);
		else if (o[i].type == 'p')
			ft_printf("pl\t%f,%f,%f\t\t%f,%f,%f\t\t\t\t\t\t\t%d,%d,%d\n",
			o[i].pos1.x, o[i].pos1.y, o[i].pos1.z, o[i].vec.x, o[i].vec.y,
			o[i].vec.z, o[i].rgb.packed.r, o[i].rgb.packed.g, o[i].rgb.packed.b);
		else if (o[i].type == 'q')
			ft_printf("sq\t%f,%f,%f\t\t%f,%f,%f\t\t%f\t\t\t\t%d,%d,%d\n",
			o[i].pos1.x, o[i].pos1.y, o[i].pos1.z, o[i].vec.x, o[i].vec.y,
			o[i].vec.z, o[i].size, o[i].rgb.packed.r, o[i].rgb.packed.g, o[i].rgb.packed.b);
		else if (o[i].type == 'c')
			ft_printf("cy\t%f,%f,%f\t\t%f,%f,%f\t\t%f\t\t%f\t%d,%d,%d\n",
			o[i].pos1.x, o[i].pos1.y, o[i].pos1.z, o[i].vec.x, o[i].vec.y,
			o[i].vec.z, o[i].dia, o[i].height, o[i].rgb.packed.r, o[i].rgb.packed.g,
			o[i].rgb.packed.b);
		else if (o[i].type == 't')
			ft_printf("tr\t%f,%f,%f\t\t%f,%f,%f\t\t%f,%f,%f\t\t%d,%d,%d\n",
			o[i].pos1.x, o[i].pos1.y, o[i].pos1.z, o[i].pos2.x, o[i].pos2.y,
			o[i].pos2.z, o[i].pos3.x, o[i].pos3.y, o[i].pos3.z, o[i].rgb.packed.r,
			o[i].rgb.packed.g, o[i].rgb.packed.b);
		i++;
	}
}
