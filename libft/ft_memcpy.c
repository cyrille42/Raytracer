/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:21:23 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 13:21:24 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	char		*dp;
	const char	*sp;

	sp = s2;
	dp = s1;
	while (n--)
		*dp++ = *sp++;
	return (s1);
}