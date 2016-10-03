/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:31:48 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/04 17:59:15 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = ft_strlen(s2);
	if (!s2)
		return ((char *)s1);
	while (((i + l) <= n) && *s1)
	{
		if (ft_memcmp(s1, s2, l) == 0)
			return (char *)(s1);
		s1++;
		i++;
	}
	return (NULL);
}
