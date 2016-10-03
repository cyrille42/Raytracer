/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_obj2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 16:59:17 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/17 17:03:16 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_parse_cube(t_info *info, t_image *screen, int fd, int id)
{
	char		*line;
	char		*tmp;

	info->type[id] = O_CUBE;
	while (get_next_line(fd, &line) && ft_strcmp("END", line) != 0)
	{
		if ((tmp = ft_strstr(line, "dir:")) != NULL)
			info->dir[id] = ft_parse_float4(tmp + 4);
		else if ((tmp = ft_strstr(line, "pos:")) != NULL)
			info->pos[id] = ft_parse_float4(tmp + ft_strlen("pos:"));
		else if (ft_parse_common_data(info, screen, line, id) == 0)
		{
			ft_putstr("Couldnt find corresponding value: ");
			ft_putendl(line);
		}
		free(line);
	}
	free(line);
}

void		ft_parse_sphere(t_info *info, t_image *screen, int fd, int id)
{
	char		*line;
	char		*tmp;

	info->type[id] = O_SPHERE;
	while (get_next_line(fd, &line) && ft_strcmp("END", line) != 0)
	{
		if ((tmp = ft_strstr(line, "rayon:")) != NULL)
			info->misc[id].w = ft_atof(tmp + ft_strlen("rayon:"));
		else if ((tmp = ft_strstr(line, "pos:")) != NULL)
			info->pos[id] = ft_parse_float4(tmp + ft_strlen("pos:"));
		else if (ft_parse_common_data(info, screen, line, id) == 0)
		{
			ft_putstr("Couldnt find corresponding value: ");
			ft_putendl(line);
		}
		free(line);
	}
	free(line);
}
