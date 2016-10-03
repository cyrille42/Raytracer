/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgremaud <mgremaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:02:29 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/16 17:34:42 by mgremaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					ft_parse_common_data(t_info *info,
	t_image *screen, char *line, int id)
{
	char	*tmp;
	int		i;

	i = 0;
	if (info->f[id] == NULL)
		info->f[id] = bh_default;
	if (ft_parse_norme(line, info, id, i) == 1)
		return (1);
	else if (ft_parse_norme2(line, info, id, screen) == 1)
		return (1);
	else if (ft_parse_norme3(line, info, id, i) == 1)
		return (1);
	else if (ft_parse_norme4(line, info, id, i) == 1)
		return (1);
	else if (ft_parse_norme5(line, info, id) == 1)
		return (1);
	else if ((tmp = ft_strstr(line, "negative:")) != NULL)
		info->misc[id].x = ft_atof(tmp + ft_strlen("negative:"));
	else
		return (0);
	return (1);
}

static	int			get_object_data(t_env *env, int fd, int index, int id)
{
	env->info.misc[id].y = -42;
	if (index == O_EYE)
		ft_parse_eye(&env->info, fd, id, env->render.screen);
	else if (index == O_LIGHT)
		ft_parse_spotlight(&env->info, env->render.screen, fd, id);
	else if (index == O_SPHERE)
		ft_parse_sphere(&env->info, env->render.screen, fd, id);
	else if (index == O_PLANE)
		ft_parse_plane(&env->info, env->render.screen, fd, id);
	else if (index == O_CONE)
		ft_parse_cone(&env->info, env->render.screen, fd, id);
	else if (index == O_CYLINDER)
		ft_parse_cylinder(&env->info, env->render.screen, fd, id);
	else if (index == O_CUBE)
		ft_parse_cube(&env->info, env->render.screen, fd, id);
	return (0);
}

static	void		find_type(t_env *env, int fd, char *line, int *id)
{
	int i;

	i = 0;
	while (env->objs_name[i] != NULL)
	{
		if (ft_strcmp(line, env->objs_name[i]) == 0)
		{
			get_object_data(env, fd, i, *id);
			*id = *id + 1;
		}
		i++;
	}
	env->info.size = *id;
	env->info.type[*id] = -1;
}

void				init_object(t_env *env, char *file)
{
	char	*line;
	int		ret;
	int		fd;
	int		id;

	id = 0;
	ft_putendl("Starting objects parsing");
	if ((fd = open(file, O_DIRECTORY)) > 0)
		fatal_error("Couldnt open folder: ", "file");
	if ((fd = open(file, O_RDONLY)) == -1)
		fatal_error("Couldnt find file: ", "file");
	line = NULL;
	if ((env->objs_name = ft_strsplit(OBJS, ' ')) == NULL)
		fatal_error("Not enough memory", NULL);
	while ((ret = get_next_line(fd, &line)) > 0)
		find_type(env, fd, line, &id);
	close(fd);
	ft_putendl(" objects has been loaded");
	free(line);
}
