/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:24:27 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 13:24:27 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*bak;

	bak = (char *)malloc(sizeof(bak) * ft_strlen(ptr));
	ft_memcpy(bak, ptr, ft_strlen(ptr));
	ptr = (char *)malloc(sizeof(char *) * size);
	ft_memcpy(ptr, bak, ft_strlen(bak));
	return (ptr);
}
