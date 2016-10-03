#define O_EYE 0
#define	O_LIGHT  1
#define	O_SPHERE 2 
#define	O_PLANE 3
#define	O_CYLINDER 4
#define	O_CONE  5 
#define O_CUBE 6
#define PI 3.1415926
/*
petit formule
*/
# define ABS(x) ((x) > 0 ? (x) : -(x))
# define MAX(x, y) ((x) > (y) ? (x) : (y))
# define MIN(x, y) ((x) < (y) ? (x) : (y))
# define SIGN(x) ((x) < 0 ? (-1) : (1))

#pragma OPENCL EXTENSION cl_khr_fp16 : enable
/* stuct */
typedef struct s_color
{
	int r;
	int g;
	int b;
	
}				t_color;

typedef struct	s_inter
{
	int			type;
	int			index;
	int			hit;
	float4		pos;
	float4		normal;
	float4		reflection;
	float		dist;
	float4		text;
}				t_inter;

float4			find_coor_sphere(float4 sphere_center, float4 inter_pos, float rayon, float frequency, int width, int height );
int				raytracer(__global int *type, __global float4 *pos, __global float4 *dir, __global float4 *misc, __global int *color, __global float *trans, __global float *refl, __global float4 *cut, __global int *texture, __global int *index_tex, float4 ray, float4 init_pos, int filter, int depth, int edit, int kek);
t_color find_tex(__global int *tex, int index_tex, t_inter inter, int kartoon);
t_color 		reflection(__global int *type, __global float4 *pos, __global float4 *dir, __global float4 *misc, __global int *color, t_inter inter, int depth, float4 raye);
t_inter cast_ray(__global int *type, __global float4 *pos, __global float4 *misc, __global float4 *dir,  __global float4 *cut, float4 ray, float4 position, int filter, __global int *tex, __global int *index_tex);
t_color 		compute_specular(float MaterialSpecular, float4 raydir, float4 viewdir, t_inter inter, t_color color, t_color lightColor, int kartoon);
t_inter 		plane_inter(float4 ray, float4 dir, float4 pos, float4 pos_ray, float mdr);
t_color			lighting_value(__global float4 *misc, __global int *color, float4 ray, t_inter inter, int i);
t_color			get_specular_light(t_color color, float4 from_light, t_inter inter);
t_color			get_light_at(__global int *type, __global float4 *pos, __global float4 *dir, __global float4 *misc,__global int *color, t_inter inter, int i);
t_color 		find_shadow(__global int *type, __global float4 *pos, __global float4 *dir, __global float4 *misc, __global int *color, float4 ray, t_color color_final, t_inter inter, int i, float4 a);
int 			light(__global int *type, __global float4 *pos, __global float4 *dir, __global float4 *misc, __global int *color, t_color color_final, t_inter inter, float4 a, int depth, float4 ray);
t_color			new_color(int r, int g, int b);
t_color			color_multiply(t_color c, float d);
int				rgb(int r, int g, int b);
int				color_to_int(t_color c);
float4 			project(float4 a, float4 b);
t_color			color_combine(t_color a, t_color b);
t_color			color_add_force(t_color a, t_color b);
t_color			color_add(t_color a, t_color b);
t_color			color_join(t_color a, t_color b);
t_color 		get_color_from_int(int a);
float4			get_vec_from_t(float4 pos, float4 dir, float t);
float4 			find_ray(int2 plan, __global int *type, __global float4 *dir, __global float4 *pos,  __global float4 *misc,  int width, int height);
float			find_deg_y(float4 dir);
int 			find_type(__global int *type, int type_of_type);
t_inter			sphere_inter(float4 ray, float4 pos_sphere, float4 pos_eye, float radius, int width, int height, int frequency);
float			vec_square_norm(float4 vec);
t_inter			cylinder_inter(float4 ray, float4 pos_cylindre, float radius, float4 cylinder_dir,float4 pos_eye, float frequency, int width, int height);
t_inter			cone_inter(float4 ray, float4 pos_cone, float alpha, float4 cone_dir,float4 pos_eye);
t_color			kek(float misc, t_color color, float4 ray, float4 normal,int kartoon);
t_inter 		cube_inter(float4 ray, float4 dir, float4 pos, float4 pos_ray);
float 			Get2DPerlinNoiseValue(float x, float y, float res);

float Get2DPerlinNoiseValue(float x, float y, float res)
{
    float tempX,tempY;
    int x0,y0,ii,jj,gi0,gi1,gi2,gi3;
    float unit = 1.0f/1.4f;
    if (res == 0)
    	res = 1;
    if (x > 10000)
    	x = 10000;
    if (y > 10000)
    	y = 10000;
    float tmp,s,t,u,v,Cx,Cy,Li1,Li2;
    float gradient2[][2] = {{unit,unit},{-unit,unit},{unit,-unit},{-unit,-unit},{1,0},{-1,0},{0,1},{0,-1}};
    unsigned int perm[] =
       {151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,
        142,8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,
        203,117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,
        74,165,71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,
        105,92,41,55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,
        187,208,89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,
        64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,
        47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,
        153,101,155,167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,
        112,104,218,246,97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,
        235,249,14,239,107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,
        127,4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,
        156,180};
    x /= res;
    y /= res;
    x0 = (int)(x);
    y0 = (int)(y);
    ii = x0 & 255;
    jj = y0 & 255;
    gi0 = perm[ii + perm[jj]] % 8;
    gi1 = perm[ii + 1 + perm[jj]] % 8;

    gi2 = perm[ii + perm[jj + 1]] % 8;
    gi3 = perm[ii + 1 + perm[jj + 1]] % 8;
    tempX = x-x0;
    tempY = y-y0;
    s = gradient2[gi0][0]*tempX + gradient2[gi0][1]*tempY;
    tempX = x-(x0+1);
    tempY = y-y0;
    t = gradient2[gi1][0]*tempX + gradient2[gi1][1]*tempY;
    tempX = x-x0;
    tempY = y-(y0+1);
    u = gradient2[gi2][0]*tempX + gradient2[gi2][1]*tempY;
    tempX = x-(x0+1);
    tempY = y-(y0+1);
    v = gradient2[gi3][0]*tempX + gradient2[gi3][1]*tempY;
    tmp = x-x0;
    Cx = 3 * tmp * tmp - 2 * tmp * tmp * tmp;
    Li1 = s + Cx*(t-s);
    Li2 = u + Cx*(v-u);
    tmp = y - y0;
    Cy = 3 * tmp * tmp - 2 * tmp * tmp * tmp;
    return (Li1 + Cy*(Li2-Li1));
}

float4 project(float4 a, float4 b)
{
	float t;

	t = dot(b, b);
	if (t)
 		return (b * ((dot(a, b)) / (t)));
 	return a;
}

float		vec_square_norm(float4 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

int find_type(__global int *type, int type_of_type)
{
	int a = 0;
	while (type[a] != type_of_type)	
		a++;
	return (a);
}

float	find_deg_y(float4 dir)
{
	float deg;

	if(isnotequal(dir.x, 0))//risque de bug parfois !
		deg = atan(dir.z / dir.x);
	return(deg);
}

float4 find_ray(int2 plan, __global int *type, __global float4 *dir, __global float4 *pos, __global float4 *misc,  int width, int height)
{
	float4  ray;
	int		a;

	ray.y = -1.0f;
	float4 kek = dir[a];
	kek.w = 0;
	kek = fast_normalize(kek);
	a = find_type(type, O_EYE);
	ray = fast_normalize(((pos[a] + kek * misc[a].w - fast_normalize(cross(ray, -kek)) * (((float)width / 2)) + ray * ((float)height / 2)) + fast_normalize(cross(ray, -kek)) * plan.x - ray * (plan.y)) - pos[a]);
	return (ray);
}

float4	get_vec_from_t(float4 pos, float4 dir, float t)
{
	dir = pos + dir * t;
	return (dir);
}

/* 
	plane intersection 
*/

t_inter 		cube_inter(float4 ray, float4 dir, float4 pos, float4 pos_ray)
{
	float4 		up;
	float4 		normal;
	float4 		tmp_pos;
	t_inter 	tmp_inter;
	t_inter 	inter;
	int dist = 	200000;


	up.y = 1;
	up.x = 0;
	up.z = 0;
	up.w = 0;
	float k = 50;
//	inter = sphere_inter(ray, pos, pos_ray, 2 * k);
	inter.hit = -1;
	dir.y = 0;
	dir = fast_normalize(dir);
	normal = dir;
	tmp_pos = pos + normal * k;
	tmp_inter = plane_inter(ray, normal, tmp_pos, pos_ray, 0);
	if (tmp_inter.hit == 1 && tmp_inter.dist < dist && fabs(tmp_inter.text.x) < k && fabs(tmp_inter.text.y) < k)
	{
		inter = tmp_inter;
		dist = inter.dist;
	}
	normal = -dir;
	tmp_pos = pos + normal * k;
	tmp_inter = plane_inter(ray, normal, tmp_pos, pos_ray, 0);
	if (tmp_inter.hit == 1 && tmp_inter.dist < dist && fabs(tmp_inter.text.x) < k && fabs(tmp_inter.text.y) < k)
	{
		inter = tmp_inter;
		dist = inter.dist;
	}
	normal = cross(dir, up);
	tmp_pos = pos + normal * k;
	tmp_inter = plane_inter(ray, normal, tmp_pos, pos_ray, 0);
	if (tmp_inter.hit == 1 && tmp_inter.dist < dist && fabs(tmp_inter.text.x) < k && fabs(tmp_inter.text.y) < k)
	{
		inter = tmp_inter;
		dist = inter.dist;
	}
	normal = -cross(dir, up);
	tmp_pos = pos + normal * k;
	tmp_inter = plane_inter(ray, normal, tmp_pos, pos_ray, 0);
	if (tmp_inter.hit == 1 && tmp_inter.dist < dist && fabs(tmp_inter.text.x) < k && fabs(tmp_inter.text.y) < k)
	{
		inter = tmp_inter;
		dist = inter.dist;
	}
//	inter.normal = -inter.normal;
	return inter;
	normal = up;
	tmp_pos = pos + normal * k;
	tmp_inter = plane_inter(ray, normal, tmp_pos, pos_ray, 0);
	if (tmp_inter.hit == 1 && tmp_inter.dist < dist && fast_length(tmp_inter.dist) < k)
	{
		inter = tmp_inter;
		dist = inter.dist;
	}
	normal = -up;
	tmp_pos = pos + normal * k;
	tmp_inter = plane_inter(ray, normal, tmp_pos, pos_ray, 0);
	if (tmp_inter.hit == 1 && tmp_inter.dist < dist && fast_length(tmp_inter.dist) < k)
	{
		inter = tmp_inter;
		dist = inter.dist;
	}
	return inter;
}

t_inter 		plane_inter(float4 ray, float4 dir, float4 pos, float4 pos_ray, float PerlinNoiseRatio)
{
	float 		t;
	t_inter 	inter;

	dir = fast_normalize(dir);
	inter.hit = 1;

	t = (dot((pos - pos_ray), dir)) / dot(dir, ray);
	inter.normal = dir;
	inter.pos = get_vec_from_t(pos_ray, ray, t);
	inter.type = O_PLANE;
	inter.dist = distance(inter.pos, pos_ray);
	if (isless(t, 0))
		inter.hit = -1;
	//q_proj = q - dot(q - p, n) * n
//	printf("%f\n", inter.dist);
	if (inter.dist > 100000)
	{
		inter.hit = -1;
		return inter;
	}
	float3 q;
	q.x = 0;
	q.y = 0;
	q.z = 1;
	float3 dirp;
	dirp.x = dir.x;
	dirp.y = dir.y;
	dirp.z = dir.z;

	float Cphi = acos((dot(dirp, q)));
	float Sphi = sin(Cphi);

	Cphi = cos(Cphi);
	float ACphi = 1.0f - Cphi;
	float3 axis = fast_normalize(cross(dirp, q));
	inter.pos -= pos;
	if (dot(dirp, q) != 1 && dot(dirp, q) != -1)
	{
		inter.text.x = fabs((Cphi + axis.x * axis.x * ACphi) * inter.pos.x + (axis.x * axis.y * ACphi - axis.z * Sphi) * inter.pos.y + (axis.x * axis.z * ACphi + axis.y * Sphi) * inter.pos.z);
		inter.text.y = fabs((axis.y * axis.x * ACphi + axis.z * Sphi) * inter.pos.x + (Cphi + axis.y * axis.y * ACphi) * inter.pos.y + (axis.y * axis.z * ACphi - axis.x * Sphi) * inter.pos.z); 
	}
	else
	{
		inter.text.x = fabs(inter.pos.x);
		inter.text.y = fabs(inter.pos.y);
	}
	//inter.text.x = ((int)inter.text.x % 100000) / 100;
	//inter.text.y = ((int)inter.text.x % 100000) / 100;
	//inter.text.x = (int)inter.text.x % 50000;
	//inter.text.y = (int)inter.text.y % 50000;
	inter.text.x /= 10;
	inter.text.y /= 10;
	if (inter.text.x > 5000)
		inter.hit = -1;
	if (inter.text.y > 5000)
		inter.hit = -1;
	//inter.text.x = (int)inter.text.x % 5000;
	//inter.text.y = (int)inter.text.y % 5000;
	inter.pos += pos;
	inter.text.z = 1;
	return (inter);
}

t_inter			cone_inter(float4 ray, float4 pos_cone,float alpha, float4 cone_dir,float4 pos_eye)
{
	t_inter		inter;
	float 		delta;
	float4		tmp;
	float t,t1,t2,tmp2,tmp3;
	float a,b,c;

	inter.hit = -1;
	//pos_cone -= pos_eye;
	cone_dir = fast_normalize(cone_dir);

	tmp = ray - cone_dir * dot(ray, cone_dir);
	tmp2 = cos(alpha) * cos(alpha);
	tmp3 = sin(alpha) * sin(alpha);
	a =  tmp2 * dot(tmp, tmp) - tmp3 * (dot(ray, cone_dir) * dot(ray, cone_dir));
	b = 2 * tmp2 * dot(ray - cone_dir * dot(ray, cone_dir), pos_eye - pos_cone - cone_dir * dot(pos_eye - pos_cone, cone_dir)) - 2 * tmp3 * dot(ray, cone_dir) * dot(pos_eye - pos_cone, cone_dir);
	tmp = pos_eye - pos_cone - cone_dir * dot(pos_eye - pos_cone, cone_dir);
	c = tmp2 * dot(tmp, tmp) - tmp3 * (dot(pos_eye - pos_cone, cone_dir) * dot(pos_eye - pos_cone, cone_dir));
	delta = b * b - 4 * a * c;
	if (isless(delta, 0))
		return (inter);
	else
	{
		delta = half_sqrt(delta);
		t1 = (-b + delta) / (2 * a);
		t2 = (-b - delta) / (2 * a);
		t = min(t1, t2);
	}
	inter.hit = 1;
	if (isless(t2, 0) && isless(t1, 0))
		inter.hit = -1;
	else if (isless(t2, 0))
		t = t1;
	else if (isless(t1, 0))
		t = t2;
	inter.pos = get_vec_from_t(pos_eye ,ray, t);
	inter.normal = fast_normalize((inter.pos - pos_cone) - project((inter.pos - pos_cone), cone_dir));
	inter.dist = fast_distance(inter.pos, pos_eye);
	inter.type = O_CONE;
	float4 p = inter.normal;
	p.y = 0;
	p = fast_normalize(p);
	inter.text.y = fabs((inter.pos.y - pos_cone.y + (sqrt(pow(pos_cone.x - inter.pos.x, 2) + pow(pos_cone.z - inter.pos.z, 2)))) / 2);
	inter.text.x = fabs(((atan2(p.x, p.z) + 1))) * (sqrt(pow(pos_cone.x - inter.pos.x, 2) + pow(pos_cone.z - inter.pos.z, 2))) / 2;
	if (inter.text.x > 5000 || inter.text.y > 5000)
	{
		inter.text.y = 10;
		inter.text.x = 10;
	}
	if (inter.text.x < 0 || inter.text.y < 0)
	{
		inter.text.y = 10;
		inter.text.x = 10;
	}
	return (inter);
}



t_inter			cylinder_inter(float4 ray, float4 pos_cylindre, float radius, float4 cylinder_dir,float4 pos_eye, float frequency, int width, int height )
{
	t_inter		inter;
	float 		delta;
	float4		tmp;
	float t[3];
	float a,b,c;

	cylinder_dir = fast_normalize(cylinder_dir); //a optimiser , faire sa dans le parseur ?
	inter.hit = -1;

	tmp = ray - (cylinder_dir * dot(ray , cylinder_dir));
	a = dot(tmp, tmp);
	b = 2 * dot(ray - (cylinder_dir * dot(ray, cylinder_dir)), pos_eye - pos_cylindre - (cylinder_dir * dot(pos_eye - pos_cylindre, cylinder_dir)));
	tmp = pos_eye - pos_cylindre - (cylinder_dir * dot(pos_eye - pos_cylindre, cylinder_dir));
	c = dot(tmp, tmp) - (radius * radius);
	delta = b * b - 4 * a * c;
	if (isless(delta, 0))
		return (inter);
	else
	{
		delta = half_sqrt(delta);
		t[0] = (-b + delta) / (2 * a);
		t[1] = (-b - delta) / (2 * a);
		t[2] = min(t[0], t[1]);
	}
	if (isless(t[1], 0) && isless(t[0], 0))
		return inter;
	else if (isless(t[1], 0))
		t[2] = t[0];
	else if (isless(t[0], 0))
		t[2] = t[1];
	inter.hit = 1;
	inter.pos = get_vec_from_t(pos_eye, ray, t[2]);
	inter.normal = fast_normalize((inter.pos - pos_cylindre) - project((inter.pos - pos_cylindre), -cylinder_dir));
	inter.dist = fast_distance(inter.pos, pos_eye);
	inter.type = O_CYLINDER;
	float4 p = inter.normal;
	p.y = 0;
	p = fast_normalize(p);
	inter.text.y = fabs((inter.pos.y - pos_cylindre.y + radius) / 2);
	inter.text.x = fabs(((atan2(p.x, p.z) + 1))) * radius / 2;
	inter.normal = -inter.normal;
	return (inter);
}

/**/

/*
intersection de la sphere
*/

float4	find_coor_sphere(float4 sphere_center, float4 inter_pos, float radius, float frequency, int width, int height )
{
	float u, c, v, t, i, j;
	float4 p;

	if (!height || !width || !frequency)
	{
		height = 1000;
		frequency = 1;
		width = 1000;
	}
	p = sphere_center - inter_pos;
	u = -asin(p.y / radius);
	if (cos(u) != 0.0)
	{
		c = p.z / (radius * cos(u));
		if (c < -1)
			c = -1;
		if (c > 1)
			c = 1;
		v = acos(c);
		// degeu_tex(&degeu);
	}
	else
		v = 0.0;
	if (p.x > 0.0)
		v = -v;
	v += PI;
	t = (float)frequency * (u / PI + 0.5);
	i = (int)((height) * (t - (int)t));
	t = 0.5 * (float)frequency * (v / PI);
	j = (int)((width) * (t - (int)t));
	if (i < 0 || j < 0)
	{
		i = 1;
		j = 1;
	}
	p.x = j;
	p.y = i;
	p.z = 0;
	p.z = 0;
	return (p);
}

t_inter			sphere_inter(float4 ray, float4 pos_sphere, float4 pos_eye, float radius, int width, int height, int frequency)
{
	float		b;
	float		delta;
	float		t[3];
	t_inter inter;

	inter.hit = -1;
	b = dot(pos_eye - pos_sphere, ray);
	delta = b * b - vec_square_norm(pos_eye - pos_sphere) + radius * radius;
	if (isless(delta, 0))
		return (inter);
	else if (isequal(delta, 0))
	{
		t[2] = -b;
		inter.hit = -1;
	}
	else
	{
		delta = half_sqrt(delta);
		t[0] = (-b + delta);
		t[1] = (-b - delta);
		t[2] = min(t[0], t[1]);
	}
	inter.hit = 1;
	if (isless(t[1], 0) && isless(t[0], 0))
		inter.hit = -1;
	else if (isless(t[1], 0))
		t[2] = t[0];
	else if (isless(t[0], 0))
		t[2] = t[1];
	inter.pos = get_vec_from_t(pos_eye, ray, t[2]);
	inter.normal = fast_normalize(inter.pos - pos_sphere);
	inter.dist = fast_distance(inter.pos, pos_eye);
	inter.type = O_SPHERE;
	float4 k;
	k.z = -1;
	k.x = 0;
	k.y = 0;

	float4 p = inter.normal;
	p.y = 0;
	p = fast_normalize(p);
	inter.text = find_coor_sphere(pos_sphere, inter.pos, radius, frequency, width ,height);
//	inter.text.y = fabs((inter.pos.y - pos_sphere.y + radius) * 2);
//	inter.text.x = fabs(((atan2(p.x, p.z) + 1))) * radius * 2;
	//printf("%f %f\n", fabs(((dot(k, p) + 1) / 2)) , inter.text.y);
	return (inter);
}

/*func color */

t_color	new_color(int r, int g, int b)
{
	t_color	ret;

	ret.r = min(r, 255);
	ret.g = min(g, 255);
	ret.b = min(b, 255);
	return (ret);
}

t_color	color_multiply(t_color c, float d)
{
	return (new_color(c.r * d, c.g * d, c.b * d));
}

int		rgb(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int		color_to_int(t_color c)
{
	return (rgb(c.r, c.g, c.b));
}

t_color	color_combine(t_color a, t_color b)
{
	return (new_color(
	(a.r + b.r) / 2.0f,
	(a.g + b.g) / 2.0f,
	(a.b + b.b) / 2.0f));
}

t_color	color_add_force(t_color a, t_color b)
{
	t_color	c;

	c.r = (a.r + b.r);
	c.g = (a.g + b.g);
	c.b = (a.b + b.b);
	c.r = min(255, c.r);
	c.g = min(255, c.g);
	c.b = min(255, c.b);
	return (c);
}

t_color	color_add(t_color a, t_color b)
{
	return (new_color(a.r + b.r, a.g + b.g, a.b + b.b));
}

t_color	color_join(t_color a, t_color b)
{
	return (new_color(a.r * b.r, a.g * b.g, a.b * b.b));
}


t_color get_color_from_int(int a)
{
	t_color color;

	color.r = (a & 0xFF);
	color.g = (a & 0xFF00) >> 8;
	color.b = (a & 0xFF0000) >> 16;
	return(color);
}

t_color 		compute_specular(float MaterialSpecular, float4 raydir, float4 viewdir, t_inter inter, t_color color, t_color lightColor, int kartoon) 
{
	float d;

	viewdir = viewdir - 2.0f * dot(raydir, inter.normal) * inter.normal;
	//raydir.x = 0;
	//raydir.y = 0;
	//raydir.z = 1;
	d = dot(raydir, viewdir);

	if (isgreater(d, 0))
	{
		if(isgreater(d,2.9) && isequal(kartoon, 42))
			return(new_color(255,255,255));
		else if(isequal(kartoon,42))
			return(color);
		d *=  d * MaterialSpecular;
		lightColor.r *= d;
		lightColor.g *= d;
		lightColor.b *= d;
		color = color_add(color, lightColor);
	}
	return (color);
}

t_color		kek(float misc, t_color color, float4 ray, float4 normal, int kartoon)
{
	float lambert;

	lambert = dot(ray, normal);
	if (isless(lambert, 0))
		lambert = 0.0f;
	if(isequal(kartoon,42))
	{

		if (lambert < 0.1)
			return(new_color(0,0,0));
		else if (lambert < 0.2)
			return(color_combine(color, new_color(5,5,5)));
		else if (lambert < 0.3)
			return(color_combine(color, new_color(10,10,10)));
		else if (lambert < 0.4)
			return(color_combine(color, new_color(15,15,15)));
		else if (lambert < 0.5)
			return(color_combine(color, new_color(20,20,20)));
		else if (lambert < 0.6)
			return(color_combine(color, new_color(25,25,25)));
		else return(color);
	}
	color.r *= lambert;
	color.g *= lambert;
	color.b *= lambert;
	return color;
}

t_color find_shadow(__global int *type, __global float4 *pos, __global float4 *dir, __global float4 *misc, __global int *color, float4 ray, t_color color_final, t_inter inter, int i, float4 inter_to_view)
{
	//t_inter	tmp_inter;

	//return color_final;
	color_final = kek(misc[i].w, color_final, ray, inter.normal, misc[find_type(type, O_EYE)].y);
	//return color_final;
	color_final = compute_specular(0.01f, ray, inter_to_view, inter, color_final, get_color_from_int(color[i]),misc[find_type(type, O_EYE)].y);
	//	return color_final;
	//tmp_inter = cast_ray(type, pos, dir, misc, color, ray, inter.pos, inter.index);
	//return color_final;

//	return color_final;
	return (color_final);
}

t_inter cast_ray(__global int *type, __global float4 *pos, __global float4 *misc, __global float4 *dir,  __global float4 *cut, float4 ray, float4 position, int filter, __global int *tex, __global int *index_tex)
{
	int index;
	t_inter inter;
	t_inter tmp_inter;
	int a = -42;

	index = 0;
	tmp_inter.dist = 200000;
	while(isgreaterequal(type[index], 0))
	{
		inter.hit = -1;
		if (isnotequal(index, filter))
		{		
			if (isequal(type[index], O_SPHERE))
				inter = sphere_inter(ray, pos[index], position, misc[index].w, tex[index_tex[index * 2]], tex[index_tex[index * 2] + 1], tex[index_tex[index * 2] + 2]);
			else if (isequal(type[index], O_CYLINDER))
				inter = cylinder_inter(ray, pos[index], misc[index].w, dir[index], position, tex[index_tex[index * 2]], tex[index_tex[index * 2] + 1], tex[index_tex[index * 2] + 2]);
			else if (isequal(type[index], O_PLANE))
				inter = plane_inter(ray, dir[index], pos[index], position , 1);
			else if (isequal(type[index], O_CONE))
				inter = cone_inter(ray, pos[index], misc[index].w, dir[index], position);
			else if (isequal(type[index], O_CUBE))
				inter = cube_inter(ray, dir[index], pos[index],position);
			if(isnotequal(inter.hit, -1)) 
			{
				if ((cut[index].w == 0) || (isless(fast_distance(inter.pos, pos[index]), cut[index].x)) || (cut[index].w == 2 && inter.text.x < cut[index].x && inter.text.y < cut[index].y))
				//if ((isless(fast_distance(inter.pos, pos[index]), cut[index].x)))
				{
					a = 1;
					if(isgreater(tmp_inter.dist,inter.dist))
					{
						tmp_inter = inter;
						tmp_inter.index = index;
					}
				}
			}
		}
		index++;
	}

	tmp_inter.hit = a;
	return (tmp_inter);
}

t_color find_tex(__global int *tex, int index_tex, t_inter inter, int kartoon)
{
	t_color color;

	int width;
	int height;
	int planx;
	int plany;

	width = tex[index_tex];
	height = tex[index_tex + 1];
//	printf("x text :%i y text :%i\n", inter.text.x, inter.text.y);

	planx = ((int)inter.text.x) % width;
	plany = ((int)inter.text.y) % height;

	if (planx > width)
		planx = 0;
	if(plany > height)
		plany = 0;
//	printf("planx :%f plan y :%f\n", inter.text.y, inter.text.x);
	//printf("index :%i\n", index_tex);
	color = get_color_from_int(tex[index_tex + 3 + planx + plany * width]);
	if (kartoon == 42)
	{
		color.r -= color.r % 126;
		color.g -= color.g % 126;
		color.b -= color.b % 126; 
	}
	return(color);
}

int		raytracer(__global int *type, __global float4 *pos, __global float4 *dir, __global float4 *misc, __global int *color, __global float *trans, __global float *refl, __global float4 *cut, __global int *tex, __global int *index_tex, float4 ray, float4 init_pos, int filter, int depth, int edit, int max_ref)
{
	t_inter 	inter;
	t_inter 	light_inter;
	t_color		final_color;
	float4 		light_ray;
	t_color 	object_color;
	t_color 	tmp_color;
	float 		perlin;

	float4 		tmp_ray;
	final_color.r = 0;
	final_color.g = 0;
	final_color.b = 0;
	float c1, c2, n;
	float Ctrans;
	float Cref;
	int tmp_filter;

	t_inter tmp_inter;
	t_color tmp_object_color;
	inter.pos = init_pos;
	Cref = 0;
	Ctrans = 0;
	for (int j = 0; isless(j, max_ref) && !(j > 0 && edit); j++)
	{
		tmp_ray = ray;
		for (int k = 0; isless(k, 2) && (!j || k == 0); k++)
		{
			if (edit && k)
				break ;
			inter = cast_ray(type, pos,  misc, dir, cut, ray, inter.pos, filter, tex,index_tex);
			if (!isequal(inter.hit, 1))
				break ;
			if (misc[inter.index].z == 3)
			{
				inter.normal.x += Get2DPerlinNoiseValue(inter.text.x, inter.text.y, 20) / 2;
				inter.normal.y += Get2DPerlinNoiseValue(inter.text.y, inter.text.x, 20) / 2;
				inter.normal.z += Get2DPerlinNoiseValue(inter.text.x, inter.text.y, 20) / 2;
				inter.normal = fast_normalize(inter.normal);
			}
			if(misc[inter.index].z >= 4 && !edit)
			{
				object_color = find_tex(tex, index_tex[(inter.index * 2) + 1], inter, 0);
				inter.normal = fast_normalize(inter.normal);
				inter.normal.x += 2 * ((float)object_color.r / 255) - 1;
				inter.normal.y += 2 * ((float)object_color.g / 255) - 1;
				inter.normal.z += 2 * ((float)object_color.b / 255) - 1;
				inter.normal = fast_normalize(inter.normal);
			}
			if(misc[inter.index].z >= 4 && !edit)
				object_color = find_tex(tex, index_tex[inter.index * 2], inter, misc[find_type(type, O_EYE)].y);
			else
				object_color = get_color_from_int(color[inter.index]);
			if (isequal(k, 0))
			{
				tmp_inter = inter;
				tmp_filter = inter.index;
				tmp_object_color = object_color;
				Ctrans = trans[inter.index]; // kek
				if (!j)
					Cref = refl[inter.index];
			}
			if (misc[inter.index].z == 1)
			{
				perlin = Get2DPerlinNoiseValue(inter.text.x, inter.text.y, 20);
				perlin /= 0.5f;
				perlin += 0.8f;
				if (perlin > 1)
					perlin = 1;
				if (perlin < 0)
					perlin = 0.3;
				object_color.r *= perlin;
				object_color.g *= perlin;
				object_color.b *= perlin;
			}
			if (misc[inter.index].z == 2)
			{
				if ( ((int)(inter.text.x / 100) % 2 && (int)(inter.text.y / 100) % 2) || (!((int)(inter.text.y / 100) % 2) && !((int)(inter.text.x / 100) % 2)))
				{
					object_color.r /= 2;
					object_color.g /= 2;
					object_color.b /= 2;
				}
			}
			for (int i = 0; isgreaterequal(type[i], 0); i++)
			{
				tmp_color = object_color;
				if (isequal(type[i], O_LIGHT))
				{
					light_ray = fast_normalize(pos[i] - inter.pos);
					
					tmp_color.r &= get_color_from_int(color[i]).r;
					tmp_color.g &= get_color_from_int(color[i]).g;
					tmp_color.b &= get_color_from_int(color[i]).b;
					tmp_color = compute_specular(0.1f, -light_ray, ray, inter, tmp_color, get_color_from_int(color[i]), misc[find_type(type, O_EYE)].y);
					tmp_color = kek(misc[i].w, tmp_color, light_ray, inter.normal,misc[find_type(type, O_EYE)].y);
					if (!edit)
						light_inter = cast_ray(type, pos,  misc, dir, cut, light_ray, inter.pos, inter.index, tex, index_tex);
					if (!edit)
						if (isequal(light_inter.hit, 1) && isless(fast_distance(light_inter.pos, inter.pos), fast_distance(pos[i], inter.pos)))
					{
						tmp_color.r /= 1.4f / MIN((trans[light_inter.index] + 0.1f), 1.4f);
						tmp_color.g /= 1.4f / MIN((trans[light_inter.index] + 0.1f), 1.4f);
						tmp_color.b /= 1.4f / MIN((trans[light_inter.index] + 0.1f), 1.4f);
					}
					tmp_color.r /= fast_distance(pos[i], inter.pos) / 1000;
					tmp_color.g /= fast_distance(pos[i], inter.pos) / 1000;
					tmp_color.b /= fast_distance(pos[i], inter.pos) / 1000;

					if (dir[i].w) // HERE ADD THE COMPONENT THAT DETERMINE IF THE LUGHT IS OMNIDIRECTINAL OR NOT
					{
						float e = dot(-light_ray, dir[i]);
						if (e < 0)
							tmp_color = color_multiply(tmp_color, 0);
						else
							tmp_color = color_multiply(tmp_color, e);
					}
					for (int e = j; isgreater(e, 0); e--)
					{	
						tmp_color.r *= Cref;
						tmp_color.g *= Cref;
						tmp_color.b *= Cref;
					}
					for (int e = k; isgreater(e, 0); e--)
					{	
						tmp_color.r *= Ctrans;
						tmp_color.g *= Ctrans;
						tmp_color.b *= Ctrans;
					}

					final_color = color_add(final_color, tmp_color);
				}
			//	if (k == 0)
			//		final_color = color_multiply(final_color, 1.0f - Ctrans);
			}
			if (j == 0 && k == 0)
			{
				final_color = color_add(final_color, color_multiply(object_color, misc[find_type(type, O_EYE)].x));
				if (depth == inter.index)
				{
					final_color.g = 0;//~final_color.b;
					final_color.r = 255;//~final_color.g;
					final_color.b = 0;//~final_color.r;
				}
			}
			filter = inter.index;
			n = 1.5; // ADD HERE RINDICE / R1INDICE BITCH
			c1 = -dot(inter.normal, ray);
			c2 = 1.0f - n * n * (1.0f - c1 * c1);
			if (c2 > 0.0f)
				ray = fast_normalize(n * ray + n * (c1 - sqrtf(c2)));
			if (Ctrans < 0.05)
				break ;
		}
		if (!isequal(inter.hit, 1))
			break ;
		filter = tmp_filter;
		ray = tmp_ray;
		inter = tmp_inter;
		object_color = tmp_object_color;;
		ray = ray - 2.0f * dot(ray, inter.normal) * inter.normal;
		if (Cref < 0.05)
			break ;
	}
	int e = final_color.r;
	final_color.r = final_color.b;
	final_color.b = e;
	return color_to_int(final_color);
}

__kernel void Rt	(__global  		read_only			int* 		type,
					__global 		read_only			float4* 	pos,
					__global  		read_only			float4* 	dir,
					__global 		read_only			float4* 	misc,
					__global		read_only			int*		color,
														int 		width,
														int 		height,
					__global		read_write			int*		im,
					__global		read_only			float*		trans,
					__global 		read_only 			float* 		refl,
					__global 		read_only 			float4* 	cut, //trans = stockage dans un tableau de la transluciditer
					__global 		read_only 			int* 		tex,
					__global 		read_only 			int* 		index_tex,
														int 		selected,
														int 		edit,
														int 		max_ref)
{
	int id;
	id = get_global_id(0);
	
	int2 plan;

	plan.x = id % width;
	plan.y = id / width;
	float4 ray;

	if(type == 0 || pos == 0 || dir == 0 ||  misc == 0 ||  color == 0 ||  im == 0 ||  trans == 0 ||  refl == 0 ||  tex == 0 ||  index_tex == 0)
	{
		im[id] = 0;
		return ;	
	}
	ray = find_ray(plan, type, dir, pos, misc, width, height);
	int b;
	b = find_type(type, O_EYE);
	//ray.x += 0.1;
	//ray = normalize(ray);
	//printf("%f %f %f\n", ray.x, ray.y, ray.z);
	//printf("%f\n\n", trans[0]);
	im[id] = raytracer(type, pos, dir, misc, color, trans, refl, cut, tex, index_tex, ray, pos[b], -1, selected, edit, max_ref + 1);
	return ;
}
