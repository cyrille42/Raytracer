/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 00:38:39 by chill             #+#    #+#             */
/*   Updated: 2016/06/17 17:04:13 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		add_tore_kek(t_env *env, int a)
{
	env->info.type[a] = O_EYE;
	env->info.misc[a].y = -42;
	env->info.dir[a].x = -0.019510;
	env->info.dir[a].y = 0.217447;
	env->info.dir[a].z = 0.971930;
	env->info.pos[a].x = 1132.268433;
	env->info.pos[a].y = -240.310242;
	env->info.pos[a].z = -1173.653809;
	env->info.misc[a].w = 1600;
	env->info.misc[a].x = 0.0;
	env->info.f[a++] = bh_default;
	env->info.type[a] = O_LIGHT;
	env->info.misc[a].y = -42;
	env->info.pos[a].x = 500;
	env->info.pos[a].y = 1000;
	env->info.pos[a].z = 2000;
	env->info.misc[a].w = 1;
	env->info.color[a] = 16711680;
	env->info.f[a++] = bh_default;
	env->info.type[a] = O_LIGHT;
	env->info.misc[a].y = -42;
	env->info.f[a] = bh_default;
	return (++a);
}

static void		add_tore(t_env *env)
{
	int		a;
	double	b;

	a = add_tore_kek(env, 0) - 1;
	env->info.pos[a].x = 500;
	env->info.pos[a].y = 1000;
	env->info.pos[a].z = 4000;
	env->info.misc[a].w = 10;
	env->info.color[a++] = 65280;
	while (a < 70)
	{
		b = a;
		env->info.type[a] = O_SPHERE;
		env->info.misc[a].y = -42;
		env->info.pos[a].y = 1000;
		env->info.pos[a].x = cos(b / 10) * 1000 + 1000;
		env->info.pos[a].z = -sin(b / 10) * 1000 + 4000;
		env->info.misc[a].w = 200;
		env->info.color[a] = 16777215;
		env->info.f[a] = bh_default;
		a++;
	}
	env->info.misc[a].y = -42;
	env->info.size = a;
	env->info.type[a - 1] = -1;
}

static void		add_hely(t_env *env)
{
	int			a;
	cl_float4	tmp;

	a = init_gen(env, 0);
	env->info.type[a] = O_LIGHT;
	env->info.misc[a].y = -42;
	env->info.pos[a].x = 0;
	env->info.pos[a].y = 5000;
	env->info.pos[a].z = -2000;
	env->info.misc[a].w = 1;
	env->info.color[a] = 16711680;
	env->info.f[a] = bh_default;
	a++;
	tmp.x = 980;
	tmp.y = 1020;
	tmp.z = -290;
	while (a < 100)
	{
		a = add_gen(env, a, 0);
	}
	env->info.misc[a].y = -42;
	env->info.size = a;
	env->info.type[a - 1] = -1;
}

void			tore_obj(t_env *env)
{
	env->key.menu = 0;
	add_tore(env);
	ft_graph(env);
	mlx_expose_hook(env->win, expose_hook, env);
	mlx_loop_hook(env->mlx, update, env);
}

void			hely_obj(t_env *env)
{
	env->key.menu = 0;
	add_hely(env);
	ft_graph(env);
	mlx_expose_hook(env->win, expose_hook, env);
	mlx_loop_hook(env->mlx, update, env);
}
