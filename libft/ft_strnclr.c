/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnclr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:30:28 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 13:30:28 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnclr(char *str, int n)
{
	char	*tmp;
	int		len;

	len = n;
	while (str[len])
		len++;
	tmp = (char *)malloc(sizeof(tmp) * len);
	len = 0;
	while (str[n])
		tmp[len++] = str[n++];
	return (tmp);
}
