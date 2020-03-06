/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raytracer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 12:05:13 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/06 12:32:40 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vect		get_px_pos(t_base *b, int x, int y)
{
	t_vect		ray;

	ray.x = ((2 * ((2 * (x + 0.5) / b->res.x_max) - 1)) - 1) * \
		(tan(b->cam.fov / 2 * M_PI / 180)) * (b->res.x_max / b->res.y_max);
	ray.y = (1 - (2 * (1 - (2 * (y + 0.5) / b->res.y_max)))) * \
		(tan(b->cam.fov / 2 * M_PI / 180));
	ray.z = -1;
	return (ray);
}

t_vect		calc_vect(t_vect start, t_vect end)
{
	t_vect	new;

	new.x = start.x - end.x;
	new.y = start.y - end.y;
	new.z = start.z - end.z;
	return (new);
}

void		raytracer(t_data *img, t_base b, t_objs *o)
{
	t_vect	p_ray;
	int		x;
	int		y;

	y = 0;
	img->addr = NULL;
	o->type = 's';
	while (y < b.res.y_max)
	{
		x = 0;
		printf("%d", x);
		while (x < b.res.x_max)
		{
			p_ray = ft_normalize(calc_vect(b.cam.pos, get_px_pos(&b, x, y)));
			// printf("%d,%d | %f,%f,%f\n", x, y, p_ray.x, p_ray.y, p_ray.z);
			// check_collision_obj();
			x++;
		}
		y++;
	}
}
