/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 17:47:59 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/06 12:12:08 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void		*errors(int error)
{
	if (error == ERR_IN_RT_FILE)
		ft_putstr("\x1b[31mERROR\x1b[0m: Wrong .rt file input!\n");
	else if (error == ERR_MALLOC)
		ft_putstr("\x1b[31mERROR\x1b[0m: Memory allocating failed.");
	else if (error == ERR_02)
		ft_putstr("\x1b[31mERROR\x1b[0m: ");
	else if (error == ERR_03)
		ft_putstr("\x1b[31mERROR\x1b[0m: ");
	return (NULL);
}
