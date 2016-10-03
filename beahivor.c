/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beahivor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgremaud <mgremaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 14:33:12 by mgremaud          #+#    #+#             */
/*   Updated: 2016/06/15 15:17:24 by mgremaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	bh_default(void *ptr, int index)
{
	ptr = ptr + index;
	return ;
}

void	bh_trans_x(void *ptr, int index)
{
	t_env	*env;

	env = ptr;
	env->info.pos[index].x += env->info.beahivor_data[index][0];
	env->info.pos[index].y += env->info.beahivor_data[index][1];
	env->info.pos[index].z += env->info.beahivor_data[index][2];
}

void	bh_rot_y(void *ptr, int index)
{
	t_env	*env;
	float	a;

	env = ptr;
	a = env->info.beahivor_data[index][4];
	env->info.pos[index].x = cos(a / env->info.beahivor_data[index][0])
		* env->info.beahivor_data[index][1] + env->info.beahivor_data[index][2];
	env->info.pos[index].z = -sin(a / env->info.beahivor_data[index][0])
		* env->info.beahivor_data[index][1] + env->info.beahivor_data[index][3];
	env->info.beahivor_data[index][4]++;
}

void	bh_scal(void *ptr, int index)
{
	t_env		*env;
	static int	a[100];

	env = ptr;
	if (env->info.misc[index].w > env->info.beahivor_data[index][2])
		a[index] = 0;
	if (env->info.misc[index].w < env->info.beahivor_data[index][1])
		a[index] = 42;
	if (a[index] == 42)
		env->info.misc[index].w += env->info.beahivor_data[index][0];
	else
		env->info.misc[index].w -= env->info.beahivor_data[index][0];
}

void	bh_rise(void *ptr, int index)
{
	t_env	*env;

	env = ptr;
	if (!env->key.rise)
		return ;
	if (env->info.beahivor_data[index][4] < env->info.beahivor_data[index][3])
	{
		env->info.pos[index].x += env->info.beahivor_data[index][0]
		/ env->info.beahivor_data[index][3];
		env->info.pos[index].y += env->info.beahivor_data[index][1]
		/ env->info.beahivor_data[index][3];
		env->info.pos[index].z += env->info.beahivor_data[index][2]
		/ env->info.beahivor_data[index][3];
	}
	env->info.beahivor_data[index][4]++;
}
