/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 11:06:11 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/18 17:40:10 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		get_char_from_int1(t_env *env)
{
	int a;

	a = 0;
	while (a < WIDTH * HEIGHT)
	{
		ft_pixelput_to_image(env->render.screen, a * 3, env->info.im[a]);
		a++;
	}
}

void			creat_bmp_file(t_env *env, long int kek, char *tmp, FILE *f)
{
	static int		n = 0;
	char			buff[1000];
	unsigned char	bmpfileheader[54];

	ft_bzero(buff, 1000);
	if (n > 998)
		return ;
	kek = 0x36EEB604B003E8;
	bmpfileheader[0] = 'B';
	bmpfileheader[1] = 'M';
	bmpfileheader[10] = 54;
	memcpy(&bmpfileheader[3], &kek, 7);
	ft_strcpy(buff, "vid/");
	ft_strcat(buff, "zzzz");
	tmp = ft_itoa(n);
	ft_memcpy(buff + 4, tmp, ft_strlen(tmp));
	free(tmp);
	ft_strcat(buff, ".bmp");
	if ((f = fopen(buff, "wb")) == NULL)
		return ;
	get_char_from_int1(env);
	fwrite(bmpfileheader, 1, 54, f);
	fwrite(env->render.screen->data, 1, WIDTH * HEIGHT * 3, f);
	fclose(f);
	n++;
}
