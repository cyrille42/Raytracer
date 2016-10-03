/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:20:25 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 13:20:26 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*m;

	if (size == 0)
		return (NULL);
	m = (void *)malloc(size);
	if (m != NULL)
	{
		ft_bzero(m, size);
		return (m);
	}
	return (NULL);
}
