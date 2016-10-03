/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:25:05 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 13:25:05 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strclr(char *s)
{
	int	i;
	int	length;

	if (s == NULL)
		return ;
	i = 0;
	length = ft_strlen(s);
	while (i < length)
	{
		s[i] = '\0';
		i++;
	}
}
