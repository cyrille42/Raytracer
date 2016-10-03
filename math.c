/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:02:29 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/17 16:28:54 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ft_hex_to_int(const char *hex)
{
	char	*str;
	int		value;
	int		char_value;
	int		i;

	str = NULL;
	str = strdup(hex);
	value = 0;
	i = -1;
	while (str[++i])
	{
		value <<= 4;
		char_value = 0;
		if (str[i] >= 'A' && str[i] <= 'F')
			char_value = str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			char_value = str[i] - 'a' + 10;
		else if (str[i] >= '0' && str[i] <= '9')
			char_value = str[i] - '0';
		else if (str[i] != 32)
			break ;
		value = value + char_value;
	}
	free(str);
	return (value);
}

cl_float4	vec_view_add(cl_float4 a, cl_float4 b, float t)
{
	cl_float4	ret;

	ret.x = a.x + b.x * t;
	ret.y = a.y + b.y * t;
	ret.z = a.z + b.z * t;
	return (ret);
}

cl_float4	vec_view_minus(cl_float4 a, cl_float4 b, float t)
{
	cl_float4	ret;

	ret.x = a.x - b.x * t;
	ret.y = a.y - b.y * t;
	ret.z = a.z - b.z * t;
	return (ret);
}

double		vec_norm(cl_float4 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

cl_float4	vec_normalize(cl_float4 vec)
{
	cl_float4	normalized;
	double		norm;

	norm = vec_norm(vec);
	normalized.x = vec.x / norm;
	normalized.y = vec.y / norm;
	normalized.z = vec.z / norm;
	return (normalized);
}
