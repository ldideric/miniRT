/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   triangle.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/25 19:02:31 by ldideric       #+#    #+#                */
/*   Updated: 2020/06/08 12:53:48 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

static int		tr_right_side(t_vect v0, t_vect v1, t_vect P, t_vect N)
{
	t_vect edge;
	t_vect vp;
	t_vect C;

	edge = vect_min(v1, v0);
	vp = vect_min(P, v0);
	C = cross_pr(edge, vp);
	if (dot(N, C) < 0)
		return (0);
	return (1);
}

t_vect			triangle(t_vect rd, t_data *data, t_objs o)
{
	t_vect N;
	t_vect P;
	double t;
	double d;

	N = cross_pr(vect_min(o.pos2, o.pos1), vect_min(o.pos3, o.pos1));
	if (fabs(dot(N, rd)) < 0.00001)
		return ((t_vect){0, 0, 0, 0});
	d = dot(N, o.pos1);
	t = (dot(N, data->b.cam.c[data->b.i_c].pos) + d) / dot(N, rd);
	if (t < 0)
		return ((t_vect){0, 0, 0, 0});
	P = vec3(rd.x * t, rd.y * t, rd.z * t);
	P = vect_plus(data->b.cam.c[data->b.i_c].pos, P);
	if (tr_right_side(o.pos1, o.pos2, P, N) == 0)
		return ((t_vect){0, 0, 0, 0});
	if (tr_right_side(o.pos2, o.pos3, P, N) == 0)
		return ((t_vect){0, 0, 0, 0});
	if (tr_right_side(o.pos3, o.pos1, P, N) == 0)
		return ((t_vect){0, 0, 0, 0});
	P.hit = 1;
	printf("[HIT]%f,%f,%f,%d", P.x, P.y, P.z, P.hit);
	return (P);
}
