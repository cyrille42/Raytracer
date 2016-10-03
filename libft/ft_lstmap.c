/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 18:45:52 by ploulidi          #+#    #+#             */
/*   Updated: 2015/03/02 18:45:52 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ret;
	t_list	*tmp;
	t_list	*i;

	if (f == NULL)
		return (NULL);
	ret = f(lst);
	if (ret == NULL)
		return (NULL);
	tmp = ret;
	i = lst->next;
	while (i != NULL)
	{
		tmp->next = f(i);
		if (tmp->next == NULL)
			return (NULL);
		tmp = tmp->next;
		i = i->next;
	}
	return (ret);
}
