/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:20:50 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 13:20:50 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char *t;

	t = (char *)s;
	if (n)
	{
		while (n)
		{
			if (*t == (char)c)
				return (t);
			t++;
			n--;
		}
		return (0);
	}
	else
		return (0);
}
