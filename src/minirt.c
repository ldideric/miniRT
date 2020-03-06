/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/30 10:28:10 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/06 12:12:08 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int				main(void)
{
	t_data		img;
	t_vars		vars;
	t_base		b;
	t_objs		*o;

	o = reader(&b);
	if (o == NULL)
		return (0);
// printer(o);
	vars.mlx = mlx_init();
	// vars.win = mlx_new_window(vars.mlx, b.res.x_max, b.res.y_max, WIN_NAME);
	img.img = mlx_new_image(vars.mlx, b.res.x_max, b.res.y_max);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian);
	// graphing(&img, b.res.x_max, b.res.y_max);
	raytracer(&img, b, o);
	// mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	// hooks(&vars);
	// mlx_loop(vars.mlx);
	return (0);
}
