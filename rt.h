/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ploulidi <ploulidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:02:29 by ploulidi          #+#    #+#             */
/*   Updated: 2016/06/18 18:16:18 by ploulidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <stdio.h>
# include <stdlib.h>

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# include "libft/libft.h"
# include "get_next_line.h"
# include "minilibx_macos/mlx.h"
# include <math.h>
# include <float.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <dirent.h>

# define MEM_SIZE (WIDTH * HEIGHT)
# define MAX_SOURCE_SIZE (0x100000)
# define PI (3.141592653589793)
# define NB_LIGHT 1
# define SIZE_LIGHT 1
# define WIDTH 1200
# define HEIGHT 1000
# define PHILIPPE 1
# define PUTE 1
# define C_CLEAR "\033[H\033[2J"
# define C_RESET "\033[0m"
# define C_BOLD "\033[1m"
# define C_REV "\033[7m"
# define C_RESET "\033[0m"
# define C_WHITE "\x1B[0m"
# define C_RED "\x1B[31m"
# define C_GREEN "\x1B[32m"
# define C_YELLOW "\x1B[33m"
# define C_BLUE "\x1B[34m"
# define C_MAGENTA "\x1B[35m"
# define C_CYAN "\x1B[36m"
# define C_GRAY "\033[22;37m"
# define OBJS ("O_EYE O_LIGHT O_SPHERE O_PLANE O_CYLINDER O_CONE O_CUBE")
# define TEXT_FREE 0
# define TEXT_TEXT 1;
# define TEXT_PERLON 2;

enum			e_object_id
{
	O_EYE = 0,
	O_LIGHT = 1,
	O_SPHERE = 2,
	O_PLANE = 3,
	O_CYLINDER = 4,
	O_CONE = 5,
	O_CUBE = 6
};

typedef struct	s_color
{
	double	r;
	double	g;
	double	b;
}				t_color;

/*
** structure carte garphique
*/

typedef	struct	s_data
{
	cl_mem		type;
	cl_mem		pos;
	cl_mem		dir;
	cl_mem		im;
	cl_mem		misc;
	cl_mem		color;
	cl_mem		trans;
	cl_mem		cut;
	cl_mem		refl;
	cl_mem		texture;
	cl_mem		index_tex;
}				t_data;

typedef struct	s_info
{
	int			*type;
	cl_float4	*pos;
	cl_float4	*dir;
	int			*color;
	cl_float4	*misc;
	cl_float	*refl;
	void		(*f[100])(void *, int);
	float		beahivor_data[100][100];
	int			width;
	int			height;
	int			*im;
	size_t		size;
	size_t		size_tex;
	cl_float	*trans;
	cl_float4	*cut;
	char		**text_name;
	int			*texture;
	int			*index_tex;
}				t_info;

typedef struct	s_image
{
	void		*mlx;
	void		*ptr;
	char		*im;
	int			endian;
	int			sizeline;
	int			bpp;
	int			opp;
	char		*data;
	int			width;
	int			height;
}				t_image;

typedef struct	s_render
{
	t_image	*screen;
}				t_render;

typedef struct	s_graph
{
	cl_program			program;
	cl_int				ret;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_mem				memobj;
	cl_kernel			kernel;
	cl_platform_id		platform_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
}				t_graph;

typedef struct	s_key
{
	int			menu;
	int			help_menu;
	int			anti_alias;
	int			lock_menu;
	int			filtre;
	int			motion_blur;
	int			stereo;
	int			rec;
	int			refl;
	int			selected;
	int			pause;
	int			play;
	int			rise;
	int			edit;
}				t_key;

typedef struct	s_ntm
{
	char		**tab;
	int			id;
	int			a;
	t_image		*screen;
	int			j;
}				t_ntm;

typedef struct	s_env
{
	char		**objs_name;
	void		*mlx;
	void		*win;
	t_render	render;
	t_info		info;
	t_graph		graph;
	t_data		data;
	t_key		key;
}				t_env;

int				key_menu(t_env *env, int k);
int				key_rt_next(t_env *env, int k, int a);
void			ft_init_graph(t_graph *graph);
void			ft_end_graph(t_graph *graph);
void			ft_build_cl(t_graph *graph);
void			anti_aliasing(t_env *env);
void			motion_blur(t_env *env);
void			filtre(t_env *env);
t_color			new_color(double r, double g, double b);
int				cpy_image(t_image tex, t_info *info, int id, int frequence);
int				ft_load_image(t_image *im, t_image *screen, char *texture);
void			get_char_from_int(t_env *env);
int				color_combine_int(int a, int t);
void			bh_rise(void *ptr, int index);
void			ft_parse_cube(t_info *info, t_image *screen, int fd, int id);
int				ft_load_image(t_image *im, t_image *screen, char *texture);
int				max_tab(char **tab);
cl_float4		vec_view_add(cl_float4 a, cl_float4 b, float t);
cl_float4		vec_view_minus(cl_float4 a, cl_float4 b, float t);
double			vec_norm(cl_float4 vec);
cl_float4		vec_normalize(cl_float4 vec);
int				cpy_image(t_image tex, t_info *info, int id, int frequence);
void			tore_obj(t_env *env);
void			hely_obj(t_env *env);
void			display_menu(t_env *env);
char			**tab_file_path(char *path);
void			start_rt(t_env *env, int k);
int				update(void *ptr);
void			init_env(t_env *env);
int				mdr(void *ptr);
void			init_event(t_env *env);
void			bh_trans_x(void *ptr, int index);
void			bh_default(void *ptr, int index);
void			bh_rot_y(void *ptr, int index);
char			*load_text_kek(char *r, t_info *i, int *l, t_ntm n);
void			bh_scal(void *ptr, int index);
void			aff_help_menu(void *m, void *w);
void			ft_reprint(t_env *env);
void			load_file_cl(char *file_name, t_graph *graph);
void			ft_init_null(t_graph *graph);
void			ft_graph(t_env *env);
void			fatal_error(char *s1, char *s2);
t_image			*new_image(t_env *env, int width, int height);
int				expose_hook(t_env *env);
void			ft_pixelput_to_image(t_image *img, int index, int color);
int				key_hook(int k, t_env *env);
void			init_object(t_env *env, char *file);
int				ft_hex_to_int(const char *hex);
void			ft_parse_eye(t_info *info, int fd, int id, t_image *screen);
void			ft_parse_cone(t_info *info, t_image *screen, int fd, int id);
void			ft_parse_cylinder(t_info *info,
	t_image *screen, int fd, int id);
void			ft_parse_cone(t_info *info, t_image *screen, int fd, int id);
void			ft_parse_plane(t_info *info, t_image *screen, int fd, int id);
void			ft_parse_spotlight(t_info *info,
	t_image *screen, int fd, int id);
void			ft_parse_sphere(t_info *info, t_image *screen, int fd, int id);
cl_float4		ft_parse_float4(char *str);
double			ft_atof(char *str);
int				ft_parse_common_data(t_info *info,
	t_image *screen, char *line, int id);
void			ft_end_graph(t_graph *graph);
void			creat_bmp_file(t_env *env, long int kek, char *tmp, FILE *f);
void			add_tex(t_info *info, t_image *screen, char *texture, int id);
int				rgb(int r, int g, int b);
void			gen_cube(t_info *info, int id);
void			video_player(t_env *env);
int				init_gen(t_env *env, int a);
int				ft_parse_norme(char *line, t_info *info, int id, int i);
int				ft_parse_norme3(char *line, t_info *info, int id, int i);
int				ft_parse_norme4(char *line, t_info *info, int id, int i);
int				ft_parse_norme5(char *line, t_info *info, int id);
int				ft_parse_norme2(char *l, t_info *i, int d, t_image *s);
void			ft_parse_cube(t_info *info, t_image *screen, int fd, int id);
int				add_gen_2(t_env *env, int a);
int				add_gen(t_env *env, int a, double b);
void			ft_parse_sphere(t_info *info, t_image *screen, int fd, int id);
#endif
