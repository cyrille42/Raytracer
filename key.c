/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:02:29 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/18 18:08:47 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_kek(t_env *env, int stereo, int n)
{
	size_t	cnt;
	size_t	a;

	cnt = MEM_SIZE;
	a = 100;
	env->info.pos[0].x += stereo * n;
	clSetKernelArg(env->graph.kernel, 13, sizeof(int), &(env->key.selected));
	clSetKernelArg(env->graph.kernel, 14, sizeof(int), &(env->key.edit));
	clSetKernelArg(env->graph.kernel, 15, sizeof(int), &(env->key.refl));
	env->graph.ret = clEnqueueWriteBuffer(env->graph.command_queue,
		env->data.pos, CL_TRUE, 0, (env->info.size + 1) *
		sizeof(cl_float4), env->info.pos, 0, NULL, NULL);
	env->graph.ret = clEnqueueNDRangeKernel(env->graph.command_queue,
		env->graph.kernel, 1, NULL, &cnt, &a, 0, NULL, NULL);
	env->graph.ret = clEnqueueTask(env->graph.command_queue,
		env->graph.kernel, 0, NULL, NULL);
}

void		ft_stereo(t_env *env, int n, int i, int stereo)
{
	int		buffer[MEM_SIZE];

	ft_kek(env, stereo, n);
	if (n == 0)
		env->graph.ret = clEnqueueReadBuffer(env->graph.command_queue,
			env->data.im, CL_TRUE, 0, MEM_SIZE * sizeof(int),
			env->info.im, 0, NULL, NULL);
	if (n == 0)
		return ;
	env->graph.ret = clEnqueueReadBuffer(env->graph.command_queue,
		env->data.im, CL_TRUE, 0, MEM_SIZE *
		sizeof(int), buffer, 0, NULL, NULL);
	env->info.pos[0].x -= stereo * n;
	while (++i < MEM_SIZE)
		if (n < 0)
		{
			if (i % WIDTH + stereo < WIDTH)
				env->info.im[i] |= buffer[i + (int)stereo] & 0xFF0000;
		}
		else if (n > 0)
		{
			if (i % WIDTH - stereo > 0)
				env->info.im[i] |= buffer[i - (int)stereo] & 0x00FFFF;
		}
}

void		ft_reprint(t_env *env)
{
	ft_bzero(env->info.im, MEM_SIZE * sizeof(int));
	ft_bzero(env->render.screen->data, WIDTH * HEIGHT * sizeof(int));
	env->graph.ret = clEnqueueWriteBuffer(env->graph.command_queue,
		env->data.dir, CL_TRUE, 0, (env->info.size + 1) *
		sizeof(cl_float4), env->info.dir, 0, NULL, NULL);
	env->graph.ret = clEnqueueWriteBuffer(env->graph.command_queue,
		env->data.misc, CL_TRUE, 0, (env->info.size + 1) *
		sizeof(cl_float4), env->info.misc, 0, NULL, NULL);
	if (!env->key.stereo && PHILIPPE == PUTE)
		ft_stereo(env, 0, -1, 0);
	else
	{
		ft_stereo(env, -1, -1, 10);
		ft_stereo(env, 1, -1, 10);
	}
}

static int	key_rt(t_env *env, int k)
{
	int a;

	a = env->key.selected;
	if (k == 53)
		env->key.menu = 42;
	if (k == 123)
		env->info.pos[a].x -= 600;
	if (k == 124)
		env->info.pos[a].x += 600;
	if (k == 0)
	{
		env->info.dir[a].x = (env->info.dir[a].x * cos(0.1)) -
		(env->info.dir[a].z * sin(0.1));
		env->info.dir[a].z = (env->info.dir[a].z * cos(0.1)) +
		(env->info.dir[a].x * sin(0.1));
	}
	if (k == 2)
	{
		env->info.dir[a].x = (env->info.dir[a].x * cos(-0.1)) -
		(env->info.dir[a].z * sin(-0.1));
		env->info.dir[a].z = (env->info.dir[a].z * cos(-0.1)) +
		(env->info.dir[a].x * sin(-0.1));
	}
	return (key_rt_next(env, k, a));
}

int			key_hook(int k, t_env *env)
{
	if (env->key.menu == 42)
		return (key_menu(env, k));
	return (key_rt(env, k));
}
