/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgremaud <mgremaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:02:29 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/15 16:57:22 by mgremaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	load_file_cl(char *file_name, t_graph *graph)
{
	FILE	*fp;
	char	*source_str;
	size_t	source_size;

	fp = fopen(file_name, "r");
	if (!fp)
	{
		fprintf(stderr, "Failed to load kernel.\n");
		exit(1);
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	graph->program = clCreateProgramWithSource(graph->context, 1,
		(const char **)&source_str, (const size_t *)&source_size, &graph->ret);
	free(source_str);
	fclose(fp);
}

void	ft_init_null(t_graph *graph)
{
	graph->device_id = NULL;
	graph->context = NULL;
	graph->command_queue = NULL;
	graph->memobj = NULL;
	graph->program = NULL;
	graph->kernel = NULL;
	graph->platform_id = NULL;
}
