/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 16:41:10 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/06 11:59:08 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}
