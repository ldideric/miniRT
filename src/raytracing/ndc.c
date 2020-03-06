/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ndc.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 11:43:32 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/06 12:36:34 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vect	ndcx(t_base *b, int x, int y)
{
	t_vect	ray;
	double	ratio;
	double	angle;

	ratio = b->res.x_max / b->res.y_max;
	ray.x = (x + 0.5) / b->res.x_max;
	ray.x = 2 * ray.x - 1;
	angle = b->cam.fov * (M_PI / 180) / 2;
	ray.x = ray.x * ratio * tan(angle);
	ray.y = (y + 0.5) / b->res.x_max;
	ray.y = 1 - 2 * ray.y;
	angle = b->cam.fov * (M_PI / 180) / 2;
	ray.y *= tan(angle);
	return (ray);
}
