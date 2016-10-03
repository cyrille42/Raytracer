/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_next.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/18 17:51:59 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/18 17:54:21 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_init_graph(t_graph *graph)
{
	graph->ret = clGetPlatformIDs(1, &graph->platform_id,
		&graph->ret_num_platforms);
	graph->ret = clGetDeviceIDs(graph->platform_id,
		CL_DEVICE_TYPE_DEFAULT, 1, &graph->device_id, &graph->ret_num_devices);
	graph->context = clCreateContext(NULL, 1,
		&graph->device_id, NULL, NULL, &graph->ret);
	graph->command_queue = clCreateCommandQueue(graph->context,
		graph->device_id, 0, &graph->ret);
}

void	ft_end_graph(t_graph *graph)
{
	graph->ret = clFlush(graph->command_queue);
	graph->ret = clFinish(graph->command_queue);
	graph->ret = clReleaseKernel(graph->kernel);
	graph->ret = clReleaseProgram(graph->program);
	graph->ret = clReleaseMemObject(graph->memobj);
	graph->ret = clReleaseCommandQueue(graph->command_queue);
	graph->ret = clReleaseContext(graph->context);
}

void	ft_build_cl(t_graph *graph)
{
	char	error[MEM_SIZE];

	graph->ret = clBuildProgram(graph->program, 1,
		&graph->device_id, "-cl-opt-disable", NULL, NULL);
	graph->ret = clGetProgramBuildInfo(graph->program,
		graph->device_id, CL_PROGRAM_BUILD_LOG, MEM_SIZE, error, NULL);
	printf("error : %s\n", error);
	graph->kernel = clCreateKernel(graph->program,
		"Rt", &graph->ret);
}

int		mdr(void *ptr)
{
	t_env *env;

	env = ptr;
	if (env->render.screen->im)
		mlx_put_image_to_window(env->mlx, env->win,
			env->render.screen->im, 0, 0);
	return (0);
}
