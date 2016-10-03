/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:31:30 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 13:31:31 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char			*alc;

	alc = ft_memalloc(sizeof(*alc) * (size + 1));
	if (alc == NULL)
		return ((char *)NULL);
	return ((char *)alc);
}
