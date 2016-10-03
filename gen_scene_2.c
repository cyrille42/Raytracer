/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_scene_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 00:38:39 by chill             #+#    #+#             */
/*   Updated: 2016/06/17 17:04:13 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		add_gen_2(t_env *env, int a)
{
	env->info.type[a] = O_CYLINDER;
	env->info.misc[a].y = -42;
	env->info.pos[a].y = 2000 + (a - 2) * 100;
	env->info.pos[a].x = 0;
	env->info.pos[a].z = 0;
	env->info.dir[a] = vec_normalize(vec_view_minus(env->info.pos[a - 1],
		env->info.pos[a - 2], 1));
	env->info.misc[a].w = 10;
	env->info.cut[a].w = 1;
	env->info.cut[a].x = 1000;
	env->info.color[a] = 16777215;
	env->info.f[a] = bh_default;
	a++;
	return (a);
}

int		add_gen(t_env *env, int a, double b)
{
	b = a;
	env->info.type[a] = O_SPHERE;
	env->info.misc[a].y = -42;
	env->info.pos[a].y = 2000 + a * 100;
	env->info.pos[a].x = cos(b / 10) * 1000 + 0;
	env->info.pos[a].z = -sin(b / 10) * 1000 + 0;
	env->info.misc[a].w = 100;
	env->info.color[a] = 16777215;
	env->info.f[a] = bh_default;
	a++;
	b = a;
	env->info.type[a] = O_SPHERE;
	env->info.misc[a].y = -42;
	env->info.pos[a].y = 2000 + (a - 1) * 100;
	env->info.pos[a].x = -cos((b - 1) / 10) * 1000 + 0;
	env->info.pos[a].z = sin(b / 10) * 1000 + 0;
	env->info.misc[a].w = 100;
	env->info.color[a] = 16777215;
	env->info.f[a] = bh_default;
	a++;
	return (add_gen_2(env, a));
}

int		init_gen(t_env *env, int a)
{
	a = 0;
	env->info.type[a] = O_EYE;
	env->info.misc[a].y = -42;
	env->info.dir[a].x = -0.019510;
	env->info.dir[a].y = 0.260945;
	env->info.dir[a].z = 0.960947;
	env->info.pos[a].x = 216.923187;
	env->info.pos[a].y = -738.006104;
	env->info.pos[a].z = -29398.221680;
	env->info.misc[a].w = 1600;
	env->info.misc[a].x = 0.0;
	env->info.f[a] = bh_default;
	a++;
	env->info.type[a] = O_LIGHT;
	env->info.misc[a].y = -42;
	env->info.pos[a].x = 0;
	env->info.pos[a].y = 20000;
	env->info.pos[a].z = -2000;
	env->info.misc[a].w = 1;
	env->info.color[a] = 16711680;
	env->info.f[a] = bh_default;
	return (++a);
}

char	*load_text_kek(char *name, t_info *info, int *last_update, t_ntm ntm)
{
	t_image	im;

	if (ft_load_image(&im, ntm.screen, ft_strtrim(ntm.tab[ntm.j])) == 0)
		exit(0);
	info->index_tex[ntm.id * 2 + ntm.j] = *last_update;
	*last_update = cpy_image(im, info, (ntm.id * 2 + ntm.j), atoi(ntm.tab[2]));
	if (name)
		name = ft_strjoin(name, ";");
	name = ft_strjoin(name, ft_strtrim(ntm.tab[0 + ntm.j]));
	name = ft_strjoin(name, ":");
	name = ft_strjoin(name, ft_itoa(info->index_tex[ntm.id * 2 + ntm.j]));
	if (*last_update < 0)
		fatal_error("ERROR:", "texture introuvable gg rito");
	return (name);
}
