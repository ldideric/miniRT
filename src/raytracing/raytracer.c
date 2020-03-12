/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raytracer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 12:05:13 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/12 17:15:32 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

t_vect			plane(t_vect rd, t_data *data)
{
	(void)rd;
	(void)data;
	return ((t_vect){0, 0, 0, 0});
}

t_vect			sphere(t_vect rd, t_data *data)
{
	t_vect p;
	double t;
	double x;
	double y;

	t = dot(vect_min(data->o[0].pos1, data->b.cam.c[data->b.i_c].pos), rd);
	p = vect_plus((t_vect){rd.x * t, rd.y * t, rd.z * t, 0}, data->b.cam.c[data->b.i_c].pos);
	y = length(vect_min(data->o[0].pos1, p));
	if (y < data->o[0].dia / 2)
	{
		x = sqrt(data->o[0].dia / 2 * data->o[0].dia / 2 - y * y);
		t = (t - x > t + x) ? t + x : t - x;
		p = (t_vect){rd.x * t, rd.y * t, rd.z * t, 0};
		p = vect_plus(p, data->b.cam.c[data->b.i_c].pos);
		p.hit = 1;
		return (p);
	}
	return ((t_vect){0, 0, 0, 0});
}

t_vect			hit_checker(t_vect rd, t_objs o, t_data *data)
{
	static const t_hit_o hit_o[128] = {
		['s'] = &sphere,
		['p'] = &plane,
	};

	return (hit_o[(int)o.type](rd, data));
}

unsigned int	first_hit(t_data *data)
{
	t_rgb	rgb;
	t_vect	hit;
	int		i;

	i = 0;
	rgb.color = 0;
	hit = (t_vect){0, 0, 0, 0};
	while (data->o[i].type)
	{
		if (data->o[i].hit.hit == 1)
		{
			rgb = data->o[i].rgb;
			hit = data->o[i].hit;
			break ;
		}
		i++;
	}
	while (data->o[i].type)
	{
		if (length_betw(hit, data->b.cam.c[data->b.i_c].pos) >
			length_betw(data->o[i].hit, data->b.cam.c[data->b.i_c].pos)
			&& data->o[i].hit.hit == 1)
		{
			rgb = data->o[i].rgb;
			hit = data->o[i].hit;
		}
		i++;
	}
	return (rgb.color);
}

unsigned int	each_px(t_vect rd, t_data *data)
{
	int i;

	i = 0;
	while (data->o[i].type)
	{
		data->o[i].hit = hit_checker(rd, data->o[i], data);
		i++;
	}
	return (first_hit(data));
}

void			px_loop(t_data *data)
{
	t_vect	px_pos;
	t_vect	ray;
	int		x;
	int		y;

	y = 0;
	px_pos.z = -1;
	printf("%d\n", data->b.i_c);
	printf("%.2f,%.2f,%.2f\n", data->b.cam.c[data->b.i_c].pos.x, data->b.cam.c[data->b.i_c].pos.y, data->b.cam.c[data->b.i_c].pos.z);
	while (y < data->b.res.y_max)
	{
		x = 0;
		px_pos.y = get_ndcy_pos(&data->b, y);
		while (x < data->b.res.x_max)
		{
			px_pos.x = get_ndcx_pos(&data->b, x);
			ray = ft_normalize(vect_min(px_pos, data->b.cam.c[data->b.i_c].pos));
			// if (x == data->b.res.x_max / 2 && y == data->b.res.y_max / 2)
			// 	printf("%f,%f,%f\n", ray.x, ray.y, ray.z);
			my_mlx_pixel_put(data, x, y, each_px(ray, data));
			x++;
		}
		y++;
	}
}
