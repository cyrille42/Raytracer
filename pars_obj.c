/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:02:29 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/17 17:51:25 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_parse_eye(t_info *info, int fd, int id, t_image *screen)
{
	char		*line;
	char		*tmp;
	int			ret;

	info->type[id] = O_EYE;
	while ((ret = get_next_line(fd, &line)) && ft_strcmp("END", line) != 0)
	{
		if ((tmp = ft_strstr(line, "dir:")) != NULL)
			info->dir[id] = ft_parse_float4(tmp + ft_strlen("dir:"));
		else if ((tmp = ft_strstr(line, "pos:")) != NULL)
			info->pos[id] = ft_parse_float4(tmp + ft_strlen("pos:"));
		else if ((tmp = ft_strstr(line, "planedist:")) != NULL)
			info->misc[id].w = ft_atof(tmp + ft_strlen("planedist:"));
		else if ((tmp = ft_strstr(line, "ambiant:")) != NULL)
			info->misc[id].x = ft_atof(tmp + ft_strlen("ambiant:"));
		else if (ft_parse_common_data(info, screen, line, id) == 0)
		{
			ft_putstr("Couldnt find corresponding value: ");
			ft_putendl(line);
		}
		free(line);
	}
	free(line);
}

void		ft_parse_cylinder(t_info *info, t_image *screen, int fd, int id)
{
	char		*line;
	char		*tmp;

	info->type[id] = O_CYLINDER;
	while (get_next_line(fd, &line) && ft_strcmp("END", line) != 0)
	{
		if ((tmp = ft_strstr(line, "rayon:")) != NULL)
			info->misc[id].w = ft_atof(tmp + ft_strlen("rayon:"));
		else if ((tmp = ft_strstr(line, "height:")) != NULL)
			info->misc[id].x = ft_atof(tmp + ft_strlen("height:"));
		else if ((tmp = ft_strstr(line, "pos:")) != NULL)
			info->pos[id] = ft_parse_float4(tmp + ft_strlen("pos:"));
		else if ((tmp = ft_strstr(line, "dir:")) != NULL)
			info->dir[id] = ft_parse_float4(tmp + ft_strlen("dir:"));
		else if (ft_parse_common_data(info, screen, line, id) == 0)
		{
			ft_putstr("Couldnt find corresponding value: ");
			ft_putendl(line);
		}
		free(line);
	}
	free(line);
}

void		ft_parse_cone(t_info *info, t_image *screen, int fd, int id)
{
	char	*line;
	char	*tmp;

	info->type[id] = O_CONE;
	while (get_next_line(fd, &line) && ft_strcmp("END", line) != 0)
	{
		if ((tmp = ft_strstr(line, "pos:")) != NULL)
			info->pos[id] = ft_parse_float4(tmp + ft_strlen("pos:"));
		else if ((tmp = ft_strstr(line, "dir:")) != NULL)
			info->dir[id] = ft_parse_float4(tmp + ft_strlen("dir:"));
		else if ((tmp = ft_strstr(line, "alpha:")) != NULL)
			info->misc[id].w = ft_atof(tmp + ft_strlen("alpha:"));
		else if (ft_parse_common_data(info, screen, line, id) == 0)
		{
			ft_putstr("Couldnt find corresponding value: ");
			ft_putendl(line);
		}
		free(line);
	}
	free(line);
}

void		ft_parse_plane(t_info *info, t_image *screen, int fd, int id)
{
	char		*line;
	char		*tmp;

	info->type[id] = O_PLANE;
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

void		ft_parse_spotlight(t_info *info, t_image *screen, int fd, int id)
{
	char	*line;
	char	*tmp;

	info->type[id] = O_LIGHT;
	while (get_next_line(fd, &line) && ft_strcmp("END", line) != 0)
	{
		if ((tmp = ft_strstr(line, "pos:")) != NULL)
			info->pos[id] = ft_parse_float4(tmp + ft_strlen("pos:"));
		else if ((tmp = ft_strstr(line, "dir:")) != NULL)
		{
			info->dir[id] = ft_parse_float4(tmp + ft_strlen("dir:"));
			info->dir[id].w = 1;
		}
		else if ((tmp = ft_strstr(line, "intensity:")) != NULL)
			info->misc[id].w = ft_atof(tmp + ft_strlen("intensity:"));
		else if (ft_parse_common_data(info, screen, line, id) == 0)
		{
			ft_putstr("Couldnt find corresponding value: ");
			ft_putendl(line);
		}
		free(line);
	}
	free(line);
}
