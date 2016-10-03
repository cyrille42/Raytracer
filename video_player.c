/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 00:38:39 by chill             #+#    #+#             */
/*   Updated: 2016/06/18 17:40:57 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		get_char_from_int1(t_env *env, char *data)
{
	int		a;

	a = 0;
	while (a < WIDTH * HEIGHT)
	{
		ft_pixelput_to_image(env->render.screen, a * env->render.screen->opp,
			((data[a * 3 + 2] << 16) & 0xFF0000) +
			((data[a * 3 + 1] << 8) & 0x00FF00)
			+ (data[a * 3] & 0xFF));
		a++;
	}
}

char			*load_bmp(char *imagepath, t_env *env)
{
	int				fd;
	unsigned char	header[54];
	char			*data;

	if ((fd = open(imagepath, O_RDONLY)) < 0 ||
		ft_strcmp(ft_strchr(imagepath, '.'), ".bmp"))
	{
		env->key.play = 0;
		return (NULL);
	}
	read(fd, header, 54);
	data = malloc(1200000 * 4);
	read(fd, data, 1200000 * 4);
	close(fd);
	return (data);
}

void			video_player(t_env *env)
{
	char		buff[1000];
	char		*data;
	char		*tmp;

	ft_strcpy(buff, "vid/");
	ft_strcat(buff, "zzzz");
	tmp = ft_itoa(env->key.play);
	ft_memcpy(buff + 4, tmp, ft_strlen(tmp));
	free(tmp);
	ft_strcat(buff, ".bmp");
	data = load_bmp(buff, env);
	if (data == NULL)
		return ;
	get_char_from_int1(env, data);
	free(data);
	env->key.play++;
}
