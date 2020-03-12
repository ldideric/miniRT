/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/30 10:28:10 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/09 19:50:44 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

int				main(void)
{
	t_data		data;
	t_vars		vars;

	data.o = reader(&data.b);
	if (data.o == NULL)
		return (0);
	// printer(data.o);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, data.b.res.x_max, data.b.res.y_max, WIN_NAME);
	data.img = mlx_new_image(vars.mlx, data.b.res.x_max, data.b.res.y_max);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.len, &data.endian);
	graphing(&data, data.b.res.x_max, data.b.res.y_max);
	px_loop(&data);
	mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
	hooks(&vars);
	mlx_loop(vars.mlx);
	return (0);
}
