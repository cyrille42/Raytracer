/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 16:09:47 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/17 17:04:35 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			max_tab(char **tab)
{
	int a;

	a = 0;
	while (tab[a])
		a++;
	return (a);
}

cl_float4	ft_get_float4(float a, float b, float c, float d)
{
	cl_float4 vec;

	vec.x = a;
	vec.y = b;
	vec.z = c;
	vec.w = d;
	return (vec);
}

cl_float4	ft_parse_float4(char *str)
{
	char		**tab;
	int			i;
	cl_float4	vec;

	i = 0;
	tab = ft_strsplit(str, ';');
	if (tab[0] && tab[1] && tab[2])
	{
		vec.x = ft_atof(tab[0]);
		vec.y = ft_atof(tab[1]);
		vec.z = ft_atof(tab[2]);
	}
	else if (tab[0] && tab[1] && tab[2] && tab[3])
		ft_get_float4(ft_atof(tab[0]), ft_atof(tab[1]), ft_atof(tab[2]),
		ft_atof(tab[3]));
	else
		ft_get_float4(0.0f, 0.0f, 0.0f, 0.0f);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (vec);
}
