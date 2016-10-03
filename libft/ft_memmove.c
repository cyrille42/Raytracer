/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:21:46 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 13:21:47 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char *d;
	char *s;

	d = (char *)dst;
	s = (char *)src;
	if (d < s)
	{
		return (ft_memcpy(dst, src, n));
	}
	else
	{
		while (n--)
		{
			d[n] = s[n];
		}
	}
	return (dst);
}
