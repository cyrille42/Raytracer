/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_norme.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 16:59:17 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/17 17:03:18 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					ft_parse_norme(char *line, t_info *info, int id, int i)
{
	char **tab;
	char *tmp;

	if ((tmp = ft_strstr(line, "rotate_y:")) != NULL)
	{
		tab = ft_strsplit(tmp + ft_strlen("rotate_y:"), ';');
		if (tab[0] && tab[1] && tab[2] && tab[3])
		{
			info->f[id] = bh_rot_y;
			info->beahivor_data[id][0] = ft_atof(tab[0]);
			info->beahivor_data[id][1] = ft_atof(tab[1]);
			info->beahivor_data[id][2] = ft_atof(tab[2]);
			info->beahivor_data[id][3] = ft_atof(tab[3]);
		}
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	else
		return (0);
	return (1);
}

int					ft_parse_norme2(char *line, t_info *info,
	int id, t_image *screen)
{
	char	*tmp;
	int		i;

	i = 0;
	if ((tmp = ft_strstr(line, "cut:")) != NULL)
		info->cut[id] = ft_parse_float4(tmp + ft_strlen("cut:"));
	else if ((tmp = ft_strstr(line, "cutMode:")) != NULL)
		info->cut[id].w = ft_atof(tmp + ft_strlen("cutMode:"));
	else if ((tmp = ft_strstr(line, "texture_data:")) != NULL)
		add_tex(info, screen, ft_strdup(tmp + ft_strlen("texture_data:")), id);
	else if ((tmp = ft_strstr(line, "texture:")) != NULL)
		info->misc[id].z = ft_atof(tmp + ft_strlen("texture:"));
	else if ((tmp = ft_strstr(line, "color:")) != NULL)
		info->color[id] = ft_hex_to_int((tmp + ft_strlen("color:")));
	else if ((tmp = ft_strstr(line, "transparency:")) != NULL)
		info->trans[id] = ft_atof((tmp + ft_strlen("transparency:")));
	else if ((tmp = ft_strstr(line, "refl:")) != NULL)
		info->refl[id] = ft_atof((tmp + ft_strlen("refl:")));
	else if ((tmp = ft_strstr(line, "limit:")) != NULL &&
		info->type[id] != O_SPHERE)
		info->misc[id].y = ft_atof((tmp + ft_strlen("limit:")));
	else
		return (0);
	return (1);
}

int					ft_parse_norme3(char *line, t_info *info, int id, int i)
{
	char	**tab;
	char	*tmp;

	if ((tmp = ft_strstr(line, "scaling:")) != NULL &&
		(info->type[id] == O_CYLINDER || info->type[id] == O_SPHERE))
	{
		tab = ft_strsplit(tmp + ft_strlen("scaling:"), ';');
		if (tab[0] && tab[1] && tab[2])
		{
			info->f[id] = bh_scal;
			info->beahivor_data[id][0] = ft_atof(tab[0]);
			info->beahivor_data[id][1] = ft_atof(tab[1]);
			info->beahivor_data[id][2] = ft_atof(tab[2]);
		}
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	else
		return (0);
	return (1);
}

int					ft_parse_norme4(char *line, t_info *info, int id, int i)
{
	char	**tab;
	char	*tmp;

	if ((tmp = ft_strstr(line, "translation:")) != NULL)
	{
		tab = ft_strsplit(tmp + ft_strlen("translation:"), ';');
		if (tab[0] && tab[1] && tab[2])
		{
			info->f[id] = bh_trans_x;
			info->beahivor_data[id][0] = ft_atof(tab[0]);
			info->beahivor_data[id][1] = ft_atof(tab[1]);
			info->beahivor_data[id][2] = ft_atof(tab[2]);
		}
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	else
		return (0);
	return (1);
}

int					ft_parse_norme5(char *line, t_info *info, int id)
{
	char	**tab;
	char	*tmp;

	if ((tmp = ft_strstr(line, "rise:")) != NULL)
	{
		tab = ft_strsplit(tmp + ft_strlen("rise:"), ';');
		if (tab[0] && tab[1] && tab[2] && tab[3])
		{
			info->f[id] = bh_rise;
			info->beahivor_data[id][0] = info->pos[id].x - ft_atof(tab[0]);
			info->beahivor_data[id][1] = info->pos[id].y - ft_atof(tab[1]);
			info->beahivor_data[id][2] = info->pos[id].z - ft_atof(tab[2]);
			info->beahivor_data[id][4] = 0;
			info->pos[id].x = ft_atof(tab[0]);
			info->pos[id].y = ft_atof(tab[1]);
			info->pos[id].z = ft_atof(tab[2]);
			info->beahivor_data[id][3] = ft_atof(tab[3]) * 14;
		}
	}
	else
		return (0);
	return (1);
}
