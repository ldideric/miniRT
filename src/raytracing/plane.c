/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 19:39:41 by ldideric      #+#    #+#                 */
/*   Updated: 2020/06/10 20:00:58 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

t_vect			plane(t_vect rd, t_data *data, t_objs o)
{
	bool intersectPlane(const Vec3f &n, const Vec3f &p0,
	const Vec3f &l0, const Vec3f &l, float &t) 

	float denom = dotProduct(n, l);
	if (denom > 1e-6) {
		Vec3f p0l0 = p0 - l0;
		t = dotProduct(p0l0, n) / denom;
		return (t >= 0);
	}

	return false;
}


// t_vect			plane(t_vect rd, t_data *data, t_objs o)
// {
// 	(void)rd;
// 	(void)data;
// 	(void)o;
// 	return ((t_vect){0, 0, 0, 0});
// }