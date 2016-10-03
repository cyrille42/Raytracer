/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:32:31 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 13:32:31 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	len;

	if (!*s2)
		return ((char*)s1);
	len = ft_strlen(s2);
	while (*s1)
	{
		if (!ft_memcmp(s1++, s2, len))
			return ((char*)s1 - 1);
	}
	return (0);
}
