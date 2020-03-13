/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:21:31 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/13 16:00:40 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

static int			cam_change_hooks(int keycode, t_vars *vars)
{
	if (keycode == 124 && vars->data.b.cam.max > 1)
	{
		if (vars->data.b.i_c == vars->data.b.cam.max - 1)
			vars->data.b.i_c = 0;
		else
			vars->data.b.i_c++;
		ft_printf("Rendering...\n");
		px_loop(&vars->data);
		ft_printf("Done!\n");
		mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	}
	else if (keycode == 123 && vars->data.b.cam.max > 1)
	{
		if (vars->data.b.i_c == 0)
			vars->data.b.i_c = vars->data.b.cam.max - 1;
		else
			vars->data.b.i_c--;
		ft_printf("Rendering...\n");
		px_loop(&vars->data);
		ft_printf("Done!\n");
		mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	}
	return (0);
}

static int			refresh_hooks(t_vars *vars)
{
	free(vars->data.o);
	ft_printf("Reading...\n");
	vars->data.o = reader(&vars->data.b, 0, 0);
	if (vars->data.o == NULL)
	{
		ft_printf("Can't refresh... check for tabs/other mistakes?\n");
		return (0);
	}
	ft_printf("Rendering...\n");
	px_loop(&vars->data);
	ft_printf("Done!\n");
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	return (0);
}

static int			button_press_hooks(int keycode, t_vars *vars)
{
	if (keycode == 53 || keycode == 12)
	{
		// reader_free(vars->data.o, vars->data.b.light, vars->data.b.cam.c, NULL);
		exit(mlx_destroy_window(vars->mlx, vars->win) * 0);
	}
	if (keycode == 123 || keycode == 124)
		cam_change_hooks(keycode, vars);
	if (keycode == 15)
		refresh_hooks(vars);
	return (0);
}

static int			destroy_notify_hooks(int x, t_vars *vars)
{
	(void)x;
	(void)vars;
	// reader_free(vars->data.o, vars->data.b.light, vars->data.b.cam.c, NULL);
	ft_printf("\x1b[38;5;196m[-]\x1b[0m Shutting down...\n");
	exit(0);
	return (0);
}

void				hooks(t_vars *vars)
{
	mlx_hook(vars->win, 2, (1L << 0), button_press_hooks, vars);
	mlx_hook(vars->win, 17, 0L, destroy_notify_hooks, vars);
	return ;
}
