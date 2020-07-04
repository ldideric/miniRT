/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raytracer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 12:05:13 by ldideric      #+#    #+#                 */
/*   Updated: 2020/06/29 15:07:01 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

t_vect			hit_checker(t_vect *rd, t_objs *o, t_data *data)
{
	static const t_hit_o hit_o[128] = {
		['s'] = &sphere,
		['p'] = &plane,
		['t'] = &triangle,
	};

	return (hit_o[(int)o->type](rd, data, o));
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

unsigned int	each_px(t_vect *rd, t_data *data)
{
	int i;

	i = 0;
	while (data->o[i].type)
	{
		data->o[i].hit = hit_checker(rd, &data->o[i], data);
		i++;
	}
	return (first_hit(data));
}

void			*px_loop(t_data *data)
{
	t_vect	px_pos;
	t_vect	ray;
	int		x;
	int		y;
	int		i;

	y = 0;
	i = data->b.i_c;
	px_pos.z = -1;
	norm_cam_printer(data);
	while (y < data->b.res.y_max)
	{
		x = 0;
		px_pos.y = get_ndcy_pos(&data->b, y);
		while (x < data->b.res.x_max)
		{
			px_pos.x = get_ndcx_pos(&data->b, x);
			ray = ft_normalize(vect_min(px_pos, data->b.cam.c[i].pos));
			my_mlx_pixel_put(data, x, y, each_px(&ray, data));
			x++;
		}
		y++;
	}
	return (NULL);
}
