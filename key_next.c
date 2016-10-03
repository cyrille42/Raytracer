/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/18 18:08:14 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/18 18:11:28 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			key_menu(t_env *env, int k)
{
	if (k == 53)
	{
		ft_end_graph(&env->graph);
		exit(EXIT_SUCCESS);
	}
	printf("%i\n", k);
	if (k == 34)
		creat_bmp_file(env, 0, NULL, NULL);
	if (k > 81 && k < 93)
		start_rt(env, k);
	if (k == 17)
		tore_obj(env);
	if (k == 16)
		hely_obj(env);
	if (k == 69)
	{
		if (max_tab(tab_file_path(".")) / (env->key.lock_menu + 1) < 10)
			env->key.lock_menu = 0;
		else
			env->key.lock_menu += 10;
	}
	return (0);
}

static int	key_rt_next3(t_env *env, int k, int a)
{
	a = a + 1;
	if (k == 33 && env->key.refl < 4)
		env->key.refl++;
	return (0);
}

static int	key_rt_next2(t_env *env, int k, int a)
{
	if (k == 15)
		env->key.rise = 1;
	if (k == 14)
		env->key.edit = !env->key.edit;
	if (k == 12)
		env->key.selected++;
	if (env->info.type[env->key.selected] < 0)
		env->key.selected = 0;
	if (k == 34)
		env->key.rec = !env->key.rec;
	if (k == 4)
	{
		if (env->key.help_menu == 42)
			env->key.help_menu = 0;
		else
			env->key.help_menu = 42;
	}
	if (k == 125)
		env->info.pos[a].z -= 1000;
	if (k == 126)
		env->info.pos[a].z += 1000;
	if (k == 46)
		env->key.motion_blur = !env->key.motion_blur;
	return (key_rt_next3(env, k, a));
}

static int	key_rt_next1(t_env *env, int k, int a)
{
	if (k == 35)
	{
		if (env->key.play == -1)
			env->key.play = 0;
		else
			env->key.play = -1;
	}
	if (k == 16)
		env->key.stereo = !env->key.stereo;
	if (k == 38)
	{
		if (env->key.filtre == 42)
			env->key.filtre = 0;
		else
			env->key.filtre = 42;
	}
	if (k == 40)
	{
		if (env->info.misc[a].y == 42)
			env->info.misc[a].y = 0;
		else
			env->info.misc[a].y = 42;
	}
	return (key_rt_next2(env, k, a));
}

int			key_rt_next(t_env *env, int k, int a)
{
	if (k == 1)
	{
		env->info.dir[a].y = (env->info.dir[a].y * cos(-0.1)) -
		(env->info.dir[a].z * sin(-0.1));
		env->info.dir[a].z = (env->info.dir[a].z * cos(-0.1)) +
		(env->info.dir[a].y * sin(-0.1));
	}
	if (k == 13)
	{
		env->info.dir[a].y = (env->info.dir[a].y * cos(0.1)) -
		(env->info.dir[a].z * sin(0.1));
		env->info.dir[a].z = (env->info.dir[a].z * cos(0.1)) +
		(env->info.dir[a].y * sin(0.1));
	}
	if (k == 31)
		env->key.pause = !(env->key.pause);
	if (k == 37)
	{
		if (env->key.anti_alias == 42)
			env->key.anti_alias = 0;
		else
			env->key.anti_alias = 42;
	}
	return (key_rt_next1(env, k, a));
}
