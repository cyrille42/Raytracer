/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:24:48 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 13:24:48 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			d;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	d = (char)c;
	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == d)
			return (((char*)s + i));
		i++;
	}
	return (NULL);
}
