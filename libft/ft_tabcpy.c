/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:33:13 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 13:33:14 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabcpy(char **tab)
{
	int		i;
	char	**ret;

	i = 0;
	while (tab[i])
		i++;
	ret = (char **)malloc(sizeof(ret) * (i + 1));
	ret[i + 1] = NULL;
	i = 0;
	while (tab[i])
	{
		ret[i] = (char *)malloc(sizeof(ret[i]) * ((ft_strlen(tab[i]) + 1)));
		ft_bzero(ret[i], ft_strlen(tab[i]) + 1);
		ft_strcpy(ret[i], tab[i]);
		i++;
	}
	return (tab);
}
