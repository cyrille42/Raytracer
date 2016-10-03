/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 13:33:02 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 13:33:02 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_white(char c)
{
	return (c == '\v' || c == '\f' || c == '\r' || c == ' ' || c == '\n' ||
		c == '\t');
}

char		*ft_strtrim(char const *s)
{
	int		a;
	int		b;
	char	*new_str;

	a = 0;
	new_str = NULL;
	while (*s && is_white(*s))
		s++;
	while (ft_isalpha(s[a]))
		a++;
	new_str = malloc(sizeof(char) * a + 1);
	b = 0;
	while (b <= a)
	{
		new_str[b] = s[b];
		b++;
	}
	new_str[b] = '\0';
	return (new_str);
}
