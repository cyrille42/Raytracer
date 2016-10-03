/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 16:35:01 by mgremaud          #+#    #+#             */
/*   Updated: 2016/06/18 17:52:11 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			creat_buff_next(t_data *data, t_info *info, t_graph *graph)
{
	data->refl = clCreateBuffer(graph->context, CL_MEM_READ_WRITE |
		CL_MEM_COPY_HOST_PTR, (info->size + 1) *
		sizeof(cl_float), info->refl, &graph->ret);
	data->cut = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
		CL_MEM_COPY_HOST_PTR, (info->size + 1) *
		sizeof(cl_float4), info->cut, &graph->ret);
	data->texture = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
		CL_MEM_COPY_HOST_PTR, (info->size_tex + 1) *
		sizeof(int), info->texture, &graph->ret);
	data->index_tex = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
		CL_MEM_COPY_HOST_PTR, ((info->size + 1) * 2) *
		sizeof(int), info->index_tex, &graph->ret);
}

void			creat_buff(t_data *data, t_info *info, t_graph *graph)
{
	data->type = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
		CL_MEM_COPY_HOST_PTR, (info->size + 1) *
		sizeof(int), info->type, &graph->ret);
	data->pos = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
		CL_MEM_COPY_HOST_PTR, (info->size + 1) *
		sizeof(cl_float4), info->pos, &graph->ret);
	data->dir = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
		CL_MEM_COPY_HOST_PTR, (info->size + 1) *
		sizeof(cl_float4), info->dir, &graph->ret);
	data->color = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
		CL_MEM_COPY_HOST_PTR, (info->size + 1) *
		sizeof(int), info->color, &graph->ret);
	data->misc = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
		CL_MEM_COPY_HOST_PTR, (info->size + 1) *
		sizeof(cl_float4), info->misc, &graph->ret);
	data->im = clCreateBuffer(graph->context, CL_MEM_READ_WRITE |
		CL_MEM_COPY_HOST_PTR, HEIGHT * WIDTH *
		sizeof(int), info->im, &graph->ret);
	data->trans = clCreateBuffer(graph->context, CL_MEM_READ_WRITE |
		CL_MEM_COPY_HOST_PTR, (info->size + 1) *
		sizeof(cl_float), info->trans, &graph->ret);
	creat_buff_next(data, info, graph);
}

void			set_kernel(t_graph *graph, t_data data, t_info *info)
{
	graph->ret = clSetKernelArg(graph->kernel, 0, sizeof(cl_mem), &data.type);
	graph->ret = clSetKernelArg(graph->kernel, 1, sizeof(cl_mem), &data.pos);
	graph->ret = clSetKernelArg(graph->kernel, 2, sizeof(cl_mem), &data.dir);
	graph->ret = clSetKernelArg(graph->kernel, 3, sizeof(cl_mem), &data.misc);
	graph->ret = clSetKernelArg(graph->kernel, 4, sizeof(cl_mem), &data.color);
	graph->ret = clSetKernelArg(graph->kernel, 5, sizeof(int), &info->width);
	graph->ret = clSetKernelArg(graph->kernel, 6, sizeof(int), &info->height);
	graph->ret = clSetKernelArg(graph->kernel, 7, sizeof(cl_mem), &data.im);
	graph->ret = clSetKernelArg(graph->kernel, 8, sizeof(cl_mem), &data.trans);
	graph->ret = clSetKernelArg(graph->kernel, 9, sizeof(cl_mem), &data.refl);
	graph->ret = clSetKernelArg(graph->kernel, 10, sizeof(cl_mem), &data.cut);
	graph->ret = clSetKernelArg(graph->kernel, 11,
		sizeof(cl_mem), &data.texture);
	graph->ret = clSetKernelArg(graph->kernel, 12,
		sizeof(cl_mem), &data.index_tex);
}

static	t_data	ft_add_info_graph_init(t_graph *graph, t_info *info)
{
	t_data	data;
	int		i;

	i = 0;
	bzero(&data, sizeof(t_data));
	creat_buff(&data, info, graph);
	while (i * sizeof(void*) < sizeof(t_data))
	{
		if (((void**)(&data))[i] == NULL)
			fatal_error("ERROR: ", "Error in Vram Allocation");
		i++;
	}
	set_kernel(graph, data, info);
	return (data);
}

void			ft_graph(t_env *env)
{
	t_graph	graph;
	size_t	cnt;

	cnt = MEM_SIZE;
	ft_init_null(&graph);
	ft_init_graph(&graph);
	load_file_cl("./Rt.cl", &graph);
	ft_build_cl(&graph);
	env->data = ft_add_info_graph_init(&graph, &env->info);
	env->graph = graph;
}
