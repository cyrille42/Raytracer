/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:02:29 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/22 18:08:56 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_env(t_env *env)
{
	env->mlx = mlx_init();
	if (env->mlx == NULL)
		fatal_error("couldnt initialize mlx", NULL);
	env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Ray tracer");
	if (env->win == NULL)
		fatal_error("couldnt initialize window", NULL);
	env->render.screen = new_image(env, WIDTH, HEIGHT);
	if (env->render.screen == NULL)
		fatal_error("not enough memory: ", "image");
	ft_putendl("Environment has been initialized");
}

int		update(void *ptr)
{
	t_env	*env;
	size_t	i;

	i = 0;
	env = ((t_env*)ptr);
	if (env->key.rec)
		creat_bmp_file(env, 0, NULL, NULL);
	while (i < env->info.size)
	{
		env->info.f[i](ptr, i);
		i++;
	}
	expose_hook(env);
	return (-42);
}

void	init_event(t_env *env)
{
	ft_graph(env);
	mlx_expose_hook(env->win, mdr, env);
	mlx_hook(env->win, 2, 1, key_hook, env);
	mlx_loop_hook(env->mlx, update, env);
	mlx_loop(env->mlx);
}

void	init_info(t_env *env)
{
	env->info.type = malloc(sizeof(int) * MEM_SIZE);
	env->info.pos = malloc(sizeof(cl_float4) * MEM_SIZE);
	env->info.dir = malloc(sizeof(cl_float4) * MEM_SIZE);
	env->info.misc = malloc(sizeof(cl_float4) * MEM_SIZE);
	env->info.cut = malloc(sizeof(cl_float4) * MEM_SIZE);
	env->info.color = malloc(sizeof(int) * MEM_SIZE);
	env->info.im = malloc(sizeof(int) * MEM_SIZE);
	env->info.trans = malloc(sizeof(float) * MEM_SIZE);
	env->info.refl = malloc(sizeof(float) * MEM_SIZE);
	env->info.texture = malloc(sizeof(int) * 2147483647);
	env->info.index_tex = malloc(sizeof(int) * MEM_SIZE);
	env->info.text_name = malloc(sizeof(char*) * MEM_SIZE);
	env->info.type[0] = -1;
	env->info.f[0] = bh_default;
	env->info.size = 0;
	env->info.size_tex = 0;
	bzero(env->info.text_name, sizeof(char*) * 1000);
	env->info.height = HEIGHT;
	env->info.width = WIDTH;
	env->key.menu = 0;
	env->key.help_menu = 0;
	env->key.anti_alias = 0;
	env->key.lock_menu = 0;
	env->key.filtre = 0;
}

int		main(void)
{
	t_env env;

	init_env(&env);
	env.key.play = -1;
	init_info(&env);
	env.render.screen->im = NULL;
	env.key.menu = 42;
	init_event(&env);
	return (0);
}
