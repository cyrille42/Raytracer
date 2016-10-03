/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 18:45:43 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 18:45:43 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*tmp;

	if (!alst)
		return ;
	tmp = *alst;
	while (tmp != NULL)
	{
		del(tmp->content, tmp->content_size);
		tmp = tmp->next;
	}
	*alst = NULL;
}
