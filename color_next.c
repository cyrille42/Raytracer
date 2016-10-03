/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_next.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/18 17:36:16 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/18 17:47:54 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_pixelput_to_image(t_image *img, int index, int color)
{
	img->data[index] = (color & 0xFF);
	img->data[index + 1] = (color & 0xFF00) >> 8;
	img->data[index + 2] = (color & 0xFF0000) >> 16;
}

void	get_char_from_int(t_env *env)
{
	int a;

	a = 0;
	if (env->key.anti_alias == 42)
		while (a++ < 4)
			anti_aliasing(env);
	a = 0;
	if (env->key.filtre)
		filtre(env);
	if (env->key.motion_blur)
		motion_blur(env);
	while (a < WIDTH * HEIGHT)
	{
		ft_pixelput_to_image(env->render.screen, a *
			(env->render.screen->opp), env->info.im[a]);
		a++;
	}
}

t_color	new_color(double r, double g, double b)
{
	t_color	ret;

	ret.r = MIN(r, 255);
	ret.g = MIN(g, 255);
	ret.b = MIN(b, 255);
	return (ret);
}

int		rgb(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void	filtre(t_env *env)
{
	int a;

	a = 0;
	while (a < WIDTH * HEIGHT)
	{
		env->info.im[a] = color_combine_int(env->info.im[a], 6502210);
		a++;
	}
}
