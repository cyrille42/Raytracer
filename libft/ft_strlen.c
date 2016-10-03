/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:28:59 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 13:29:00 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlen(const char *str)
{
	int a;

	a = 0;
	while (*str != '\0')
	{
		str = str + 1;
		a = a + 1;
	}
	return (a);
}
