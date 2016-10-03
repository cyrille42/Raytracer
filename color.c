/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/18 17:34:40 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/18 17:35:51 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	color_combine(t_color a, t_color b)
{
	return (new_color(
	(a.r + b.r) / 2.0,
	(a.g + b.g) / 2.0,
	(a.b + b.b) / 2.0));
}

int		color_to_int(t_color c)
{
	return (rgb(c.b, c.g, c.r));
}

t_color	ft_color(int c)
{
	t_color	color;

	color.r = MIN(((c >> 16) & 0xFF), 255);
	color.g = MIN(((c >> 8) & 0xFF), 255);
	color.b = MIN((c & 0xFF), 255);
	return (color);
}

t_color	get_color_from_int(int a)
{
	t_color color;

	color.r = (a & 0xFF);
	color.g = (a & 0xFF00) >> 8;
	color.b = (a & 0xFF0000) >> 16;
	return (color);
}

int		color_combine_int(int a, int t)
{
	cl_int3 c;
	cl_int3 c1;

	c1.x = (t >> 16) & 0xFF;
	c1.y = (t >> 8) & 0xFF;
	c1.z = t & 0xFF;
	c.x = (a >> 16) & 0xFF;
	c.y = (a >> 8) & 0xFF;
	c.z = a & 0xFF;
	return ((((c.x + c1.x) / 2) & 0xff) << 16) +
	((((c.y + c1.y) / 2) & 0xff) << 8) + (((c.z + c1.z) / 2) & 0xff);
}
