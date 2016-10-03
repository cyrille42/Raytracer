/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:02:29 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/01 16:05:16 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	ft_atof_do(char *str, int sign, int in_fraction, int divisor)
{
	double	integer;
	double	fraction;

	integer = 0;
	fraction = 0;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
		{
			if (in_fraction && (divisor = divisor * 10))
				fraction = fraction * 10 + (*str - '0');
			else
				integer = integer * 10 + (*str - '0');
		}
		else
		{
			if (!in_fraction && *str != '.')
				break ;
			else
				in_fraction = 1;
		}
		++str;
	}
	return (sign * (integer + fraction / divisor));
}

double			ft_atof(char *str)
{
	int		sign;

	if (str == NULL || !*str)
		return (0);
	if (ft_strstr(str, "MAX") != NULL)
		return (DBL_MAX);
	if (ft_strstr(str, "MIN") != NULL)
		return (-DBL_MAX);
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n'))
		str++;
	sign = 1;
	if (*str == '-')
	{
		++str;
		sign = -1;
	}
	else if (*str == '+')
		++str;
	return (ft_atof_do(str, sign, 0, 1));
}
