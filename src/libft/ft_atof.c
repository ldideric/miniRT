/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atof.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ldideric <ldideric@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 06:54:20 by ldideric       #+#    #+#                */
/*   Updated: 2020/03/06 11:59:08 by ldideric      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static double	atof_ext(char *c, const char *str, int len, int i)
{
	double res2;

	res2 = (double)ft_atoi(c);
	while (str[i] != '.')
		i++;
	i++;
	while (ft_isdigit(str[i + len]))
		len++;
	while (len > 0)
	{
		res2 /= 10;
		len--;
	}
	return (res2);
}

double			ft_atof(const char *str)
{
	double	res;
	double	res2;
	char	*c;

	if (str == NULL)
		return (0);
	c = (char *)str;
	res = (double)ft_atoi(c);
	while (*c && *c != '.' && *c != ',' && *c != ' ' && *c != '\t')
		c++;
	if (*c != '.')
		return (res);
	c++;
	res2 = atof_ext(c, str, 0, 0);
	return (res + ((res >= 0) ? res2 : -res2));
}
