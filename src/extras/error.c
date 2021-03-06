/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 17:47:59 by ldideric      #+#    #+#                 */
/*   Updated: 2020/08/31 19:19:23 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <extra.h>

void		*errors(int error)
{
	if (error == ERR_NO_RT)
		ft_putstr("\x1b[31mERROR\x1b[0m:\nNO .rt file given!");
	else if (error == ERR_IN_RT_FILE)
		ft_putstr("\x1b[31mERROR\x1b[0m:\nWrong .rt file input!\n");
	else if (error == ERR_MALLOC)
		ft_putstr("\x1b[31mERROR\x1b[0m:\nMemory allocating failed.");
	else if (error == ERR_MLX)
		ft_putstr("\x1b[31mERROR\x1b[0m:\nSomething went wrong \
				with the mlx library!");
	return (NULL);
}
