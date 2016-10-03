/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgremaud <mgremaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:02:29 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/16 17:17:38 by mgremaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ft_load_image1(t_image *im, t_image *screen, char *path)
{
	im->ptr = mlx_xpm_file_to_image(screen->mlx,
		path, &im->width, &im->height);
	if (im->ptr == NULL)
	{
		ft_putstr("Couldnt find textures: ");
		ft_putendl(path);
		return (0);
	}
	im->im = mlx_get_data_addr(im->ptr, &(im->bpp),
		&(im->sizeline), &(im->endian));
	if (im->im == NULL)
	{
		ft_putendl("Not enough memory.");
		return (0);
	}
	im->opp = im->bpp / 8;
	return (1);
}

int			ft_load_image(t_image *im, t_image *screen, char *texture)
{
	char *name;

	name = ft_strjoin(ft_strdup("img/"), ft_strtrim(texture));
	name = ft_strjoin(name, ft_strdup(".xpm"));
	if (ft_load_image1(im, screen, name) == 1)
		ft_putendl("add texture");
	else
	{
		ft_putendl("not put texture");
		free(name);
		return (0);
	}
	free(name);
	return (1);
}

int			cpy_image(t_image tex, t_info *info, int id, int frequence)
{
	int a;
	int x;

	info->texture[info->index_tex[id]] = tex.width;
	info->texture[info->index_tex[id] + 1] = tex.height;
	info->texture[info->index_tex[id] + 2] = frequence;
	a = 0;
	x = 0;
	while (a < tex.width * tex.height)
	{
		info->texture[info->index_tex[id] + 3 + a] = rgb(tex.im[x + 2],
			tex.im[x + 1], tex.im[x]);
		x += 4;
		a++;
	}
	return (info->index_tex[id] + a + 3);
}

int			find_same(char *name, char *tex)
{
	char	**tab;
	int		a;

	return (-1);
	a = 0;
	if (name == NULL)
		return (-1);
	tab = ft_strsplit(name, ';');
	while (tab[a])
	{
		if (ft_strstr(tab[a], tex) != NULL)
		{
			tab = ft_strsplit(tab[a], ':');
			return (atoi(tab[1]));
		}
		a++;
	}
	return (-1);
}

void		add_tex(t_info *info, t_image *screen, char *texture, int id)
{
	static char		*name = NULL;
	static int		last_update = 0;
	t_ntm			ntm;

	bzero(&ntm, sizeof(t_ntm));
	ntm.id = id;
	ntm.screen = screen;
	ntm.tab = NULL;
	if (id < 0)
		return ;
	info->misc[ntm.id].z = 4;
	ntm.tab = ft_strsplit(texture, ';');
	if (!ntm.tab[0] || !ntm.tab[1] || !ntm.tab[2])
		return ;
	if ((ntm.a = find_same(name, ft_strtrim(ntm.tab[0]))) >= 0)
		info->index_tex[ntm.id * 2] = ntm.a;
	else
		name = load_text_kek(name, info, &last_update, ntm);
	ntm.j = 1;
	if ((ntm.a = find_same(name, ft_strtrim(ntm.tab[1]))) >= 0 &&
		info->index_tex[ntm.id * 2] >= 0)
		info->index_tex[(ntm.id * 2) + 1] = ntm.a;
	else
		name = load_text_kek(name, info, &last_update, ntm);
	info->size_tex = last_update;
}
