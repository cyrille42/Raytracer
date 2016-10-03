/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:30:55 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 13:30:57 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int a;

	a = 0;
	while (a != n)
	{
		dest[a] = src[a];
		a++;
		if (src[a] == '\0')
		{
			while (dest[a] != '\0')
			{
				dest[a] = '\0';
				a++;
			}
			return (dest);
		}
	}
	return (dest);
}
