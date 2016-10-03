/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 00:33:05 by chill             #+#    #+#             */
/*   Updated: 2016/06/20 18:30:32 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	delet_object(t_env *env)
{
	int a;

	a = 0;
	while (env->info.type[a] >= 0)
	{
		env->info.type[a] = -1;
		env->info.pos[a] = (cl_float4){{0, 0, 0, 0}};
		env->info.dir[a] = (cl_float4){{0, 0, 0, 0}};
		env->info.misc[a] = (cl_float4){{0, 0, 0, 0}};
		env->info.color[a] = 0;
		env->info.refl[a] = 0;
		env->info.trans[a] = 0;
		env->info.f[a] = bh_default;
		env->info.cut[a] = (cl_float4){{0, 0, 0, 0}};
		add_tex(NULL, NULL, NULL, -1);
		a++;
	}
	env->info.size = 0;
}

char	**tab_file_path(char *path)
{
	DIR				*ret;
	struct dirent	*readfile;
	char			**tab;
	int				a;

	a = 0;
	readfile = NULL;
	tab = malloc(sizeof(char) * 10000);
	ret = opendir(path);
	while ((readfile = readdir(ret)) != NULL)
	{
		if (ft_strstr(readfile->d_name, ".rt") != NULL)
		{
			tab[a] = ft_strdup(readfile->d_name);
			a++;
		}
	}
	tab[a] = NULL;
	return (tab);
}

void	start_rt(t_env *env, int k)
{
	char	**tab;
	int		i;

	tab = tab_file_path(".");
	if (k > 90)
		k--;
	if (max_tab(tab) > (k + env->key.lock_menu) - 82)
	{
		delet_object(env);
		init_object(env, tab[k + env->key.lock_menu - 82]);
	}
	else
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	ft_graph(env);
	env->key.menu = 0;
	mlx_expose_hook(env->win, expose_hook, env);
	mlx_loop_hook(env->mlx, update, env);
}

void	aff_help_menu(void *m, void *w)
{
	mlx_string_put(m, w, 20, 50, 0xFFFFFF, "w : rotate_y+");
	mlx_string_put(m, w, 20, 80, 0xFFFFFF, "s : rotate_y-");
	mlx_string_put(m, w, 20, 110, 0xFFFFFF, "d : rotate_x+");
	mlx_string_put(m, w, 20, 140, 0xFFFFFF, "a : rotate_x-");
	mlx_string_put(m, w, 20, 170, 0xFFFFFF, "up : forward");
	mlx_string_put(m, w, 20, 200, 0xFFFFFF, "down : step back");
	mlx_string_put(m, w, 20, 230, 0xFFFFFF, "left : left");
	mlx_string_put(m, w, 20, 260, 0xFFFFFF, "right : right");
	mlx_string_put(m, w, 20, 290, 0xFFFFFF, "i : record video");
	mlx_string_put(m, w, 20, 320, 0xFFFFFF, "esc : revenir au menu");
	mlx_string_put(m, w, 20, 350, 0xFFFFFF, "l : anti_aliasing");
	mlx_string_put(m, w, 20, 370, 0xFFFFFF, "j : filtre sepia");
	mlx_string_put(m, w, 20, 400, 0xFFFFFF, "k : effet kartoon");
	mlx_string_put(m, w, 20, 430, 0xFFFFFF, "y : vision stereoscopique");
	mlx_string_put(m, w, 20, 460, 0xFFFFFF, "p : start video");
}

void	display_menu(t_env *env)
{
	char	**tab;
	int		a;

	tab = tab_file_path(".");
	a = 0;
	mlx_string_put(env->mlx, env->win, 300, 30, 0x00FFFF,
		"Choose your file !!");
	mlx_string_put(env->mlx, env->win, 40, 500, 0xFF00FF, "esc : Quit");
	mlx_string_put(env->mlx, env->win, 600, 500, 0xFF00FF, "t : torus");
	mlx_string_put(env->mlx, env->win, 600, 530, 0xFF00FF, "y : helicoid");
	mlx_string_put(env->mlx, env->win, 670, 280, 0xFF00FF, "+ : next--->");
	while (tab[a + env->key.lock_menu])
	{
		if (a >= env->key.lock_menu + 10)
			break ;
		mlx_string_put(env->mlx, env->win, 300, a * 50 +
			100, 0xFFFFFF, ft_itoa(a));
		mlx_string_put(env->mlx, env->win, 380, a * 50 +
			100, 0xFFFFFF, tab[a + env->key.lock_menu]);
		a++;
	}
	a = -1;
	while (tab[++a])
		free(tab[a]);
	free(tab);
}
