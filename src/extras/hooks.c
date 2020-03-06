/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:21:31 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/06 12:12:08 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int			button_press_hooks(int keycode, t_vars *vars)
{
	if (keycode == 53 || keycode == 12)
		exit(mlx_destroy_window(vars->mlx, vars->win) * 0);
	return (0);
}

static int			destroy_notify_hooks(int x, t_vars *vars)
{
	(void)vars;
	(void)x;
	exit(0);
	return (0);
}

void				hooks(t_vars *vars)
{
	mlx_hook(vars->win, 2, (1L << 0), button_press_hooks, vars);
	mlx_hook(vars->win, 17, 0L, destroy_notify_hooks, vars);
	return ;
}
