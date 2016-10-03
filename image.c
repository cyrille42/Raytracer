/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:02:29 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/18 17:46:16 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_image	*new_image(t_env *env, int width, int height)
{
	t_image	*img;

	img = (t_image*)malloc(sizeof(t_image));
	if (img == NULL)
		return (NULL);
	img->ptr = mlx_new_image(env->mlx, width, height);
	if (img->ptr == NULL)
	{
		free(img);
		return (NULL);
	}
	img->data = mlx_get_data_addr(img->ptr, &(img->bpp),
			&(img->sizeline), &(img->endian));
	if (img->data == NULL)
		return (NULL);
	img->mlx = env->mlx;
	img->width = width;
	img->height = height;
	img->opp = img->bpp / 8;
	return (img);
}

void	anti_aliasing(t_env *env)
{
	int a;
	int tmp;

	a = 0;
	while (a < WIDTH * HEIGHT)
	{
		if (a + 1 < WIDTH * HEIGHT)
			tmp = color_combine_int(env->info.im[a], env->info.im[a + 1]);
		if (a + WIDTH < WIDTH * HEIGHT)
			tmp = color_combine_int(env->info.im[a], env->info.im[a + WIDTH]);
		env->info.im[a] = tmp;
		a++;
	}
}

void	motion_blur(t_env *env)
{
	static int	*tmp_image = NULL;
	int			a;

	a = 0;
	if (tmp_image != NULL)
	{
		while (a < WIDTH * HEIGHT)
		{
			env->info.im[a] = color_combine_int(env->info.im[a], tmp_image[a]);
			a++;
		}
	}
	else
	{
		tmp_image = malloc(sizeof(int) * WIDTH * HEIGHT + 1);
	}
	a = 0;
	while (a < WIDTH * HEIGHT)
	{
		tmp_image[a] = env->info.im[a];
		a++;
	}
}

void	ft_fps(t_env *env)
{
	static int		fps = 0;
	static time_t	after = 0.0f;
	time_t			now;
	static char		*curent = NULL;

	time(&now);
	if (after != now)
	{
		free(curent);
		curent = ft_itoa(fps);
		fps = 0;
	}
	else
		fps++;
	mlx_string_put(env->mlx, env->win, 20, 20, 0xFFFFFF, "fps :");
	mlx_string_put(env->mlx, env->win, 80, 20, 0xFFFFFF, curent);
	mlx_string_put(env->mlx, env->win, WIDTH - 240, HEIGHT - 30,
		0xFFFFFF, "press 'h' for help menu");
	if (env->key.rec)
		mlx_string_put(env->mlx, env->win, 200, 200, 0xFF << 16, "* REC *");
	if (env->key.stereo)
		mlx_string_put(env->mlx, env->win, 500, 200, 0xFF << 0, "* 3D ! *");
	after = now;
}

int		expose_hook(t_env *env)
{
	t_image	*img;

	img = env->render.screen;
	if (env->key.pause)
		return (0);
	if (env->key.play < 0)
		ft_reprint(env);
	else
		video_player(env);
	if (env->key.play < 0)
		get_char_from_int(env);
	mlx_put_image_to_window(env->mlx, env->win, img->ptr, 0, 0);
	ft_fps(env);
	if (env->key.menu == 42)
		display_menu(env);
	if (env->key.help_menu == 42 && env->key.menu == 0)
		aff_help_menu(env->mlx, env->win);
	return (0);
}
