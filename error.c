/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:02:29 by ploulidi          #+#    #+#             */
/*   Updated: 2015/12/09 09:22:33 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		fatal_error(char *s1, char *s2)
{
	ft_putstr(C_RED);
	ft_putstr(s1);
	ft_putendl(s2);
	ft_putstr(C_RESET);
	exit(EXIT_FAILURE);
}
