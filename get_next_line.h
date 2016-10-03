/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:02:29 by ploulidi          #+#    #+#             */
/*   Updated: 2015/12/09 09:22:33 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <fcntl.h>

# define BUFF_SIZE	1

int			get_next_line(const int fd, char **line);
size_t		lenline(char *str);
char		*ft_readline(const int fd, char *ligne, char *buf, int *ret);

#endif
