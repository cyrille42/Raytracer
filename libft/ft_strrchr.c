/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:32:05 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 13:32:05 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*t;

	t = (char *)s;
	t = t + ft_strlen(s);
	while (*t != (char)c && t != s)
		t--;
	if (*t == (char)c)
		return ((char *)t);
	return (NULL);
}
