/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:28:26 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 13:28:26 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	b;
	int				len;
	int				a;

	if (s != NULL && f != NULL)
	{
		len = ft_strlen(s);
		b = 0;
		a = 0;
		while (a < len)
		{
			(*f)(b, s);
			s++;
			b++;
			a++;
		}
	}
}
