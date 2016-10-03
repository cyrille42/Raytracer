/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:02:29 by ploulidi          #+#    #+#             */
/*   Updated: 2015/12/09 09:22:33 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	copy_data_into_line(char **data, char **line, char *loc)
{
	char	*tmp;
	int		len;
	int		i;

	len = loc - *data + 1;
	i = 0;
	if (line == NULL || (*line = (char*)malloc(sizeof(char) * len)) == NULL)
		return ;
	while (i < len - 1)
	{
		(*line)[i] = (*data)[i];
		i++;
	}
	(*line)[i] = '\0';
	tmp = ft_strdup(loc + 1);
	free(*data);
	*data = tmp;
}

void	copy_end_data(char **data, char **line, int r)
{
	int	i;

	if (r == 0 && *data)
		r = ft_strlen(*data);
	i = 0;
	if (line == NULL || (*line = (char*)malloc(sizeof(char) * (r + 1))) == NULL)
		return ;
	while (i < r)
	{
		(*line)[i] = (*data)[i];
		i++;
	}
	(*line)[r] = '\0';
	free(*data);
	*data = NULL;
}

int		add_data(char **data, char buffer[8192 + 1])
{
	char	*tmp;

	if (*data == NULL)
	{
		*data = ft_strdup(buffer);
		if (*data == NULL)
			return (-1);
	}
	else
	{
		tmp = ft_strjoin(*data, buffer);
		if (tmp == NULL)
			return (-1);
		free(*data);
		*data = tmp;
	}
	return (1);
}

int		get_next_line(int const fd, char **line)
{
	static char *data = NULL;
	char		buffer[8192 + 1];
	int			r;
	char		*loc;

	loc = NULL;
	while ((r = read(fd, buffer, 8192)) > 0)
	{
		buffer[r] = '\0';
		if (add_data(&data, buffer) == -1)
			return (-1);
		if ((loc = ft_strchr(data, '\n')) != NULL)
			break ;
	}
	if (r == -1)
		return (-1);
	else if ((loc = ft_strchr(data, '\n')) != NULL)
	{
		copy_data_into_line(&data, line, loc);
		return (1);
	}
	copy_end_data(&data, line, r);
	return (0);
}
