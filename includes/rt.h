/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 21:09:11 by ataranov          #+#    #+#             */
/*   Updated: 2018/06/12 19:49:06 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft.h"
# include "get_next_line.h"
# include "parson.h"
# include <errno.h>
# include <mlx.h>
# include <time.h>
# include <math.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include "SDL2/SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"
# include "OpenCL/opencl.h"
# include "tinyfiledialogs.h"
# include "open_cl.h"
# include "gui.h"

# define WIDTH 1024
# define HEIGHT 768
# define FOV_X 30
# define FOV_Y 30
# define LIGHT_TYPE_AMBIENT 0
# define LIGHT_TYPE_POINT 1
# define LIGHT_TYPE_DIRECT 2
# define NUM_BUTTONS 14
# define NUM_SP_PR 8
# define NUM_IC_PR 11
# define NUM_PL_PR 10
# define NUM_TR_PR 12
# define NUM_CN_PR 11
# define NUM_CU_PR 10
# define NUM_QUA_PR 10
# define NUM_EL_PR 11
# define NUM_PR_PR 10
# define NUM_LI_PR 4
# define NUM_AM_PR 1
# define NUM_DIR_PR 4
# define MAX_TEXT_LEN 150
# define PORT 50000
# define SER_SIZE 48

typedef	void			t_func(cl_float3 *ps, cl_float3 *nul_dot, float l);

typedef union			u_color
{
	int					color;
	struct
	{
		unsigned char	blue;
		unsigned char	green;
		unsigned char	red;
		unsigned char	alpha;
	}					spectrum;
}						t_color;

typedef union			u_double
{
	double				value;
	unsigned char		bytes[sizeof(double)];
}						t_double;

typedef enum			e_figure_type
{
	InfinitePlane = 0,
	Sphere,
	InfiniteCylinder,
	InfiniteCone,
	Triangle,
	Cube,
	Quadrate,
	Elipsoid,
	Parabaloid,
	Tor
}						t_figure_type;

typedef enum			e_server_client
{
	Server = -1,
	Normal,
	Client
}						t_server_client;

typedef struct			s_vector
{
	double				x;
	double				y;
	double				z;
}						t_vector;

typedef struct			s_light
{
	char				type;
	double				inten;
	t_vector			o;
	t_vector			d;
	struct s_light		*next;
}						t_light;

typedef struct			s_ray
{
	t_vector			o;
	t_vector			v;
}						t_ray;

typedef struct			s_iplane
{
	t_vector			normale;
	t_vector			point;
}						t_iplane;

typedef struct			s_capses
{
	t_iplane			*plane;
	t_color				color;
	char				enable_caps;
}						t_capses;

typedef struct			s_parabaloid
{
	t_vector			position;
	t_vector			rotation;
	double				radius;
	t_vector			capses[1];
	double				c_distances[1];
	int					c_color[1];
	t_capses			*caps;
}						t_parabaloid;

typedef struct			s_sphere
{
	t_vector			center;
	double				radius;
}						t_sphere;

typedef struct			s_icone
{
	t_vector			vertex;
	t_vector			vector;
	double				radius;
	t_vector			capses[2];
	double				c_distances[2];
	int					c_color[2];
}						t_icone;

typedef struct			s_icylinder
{
	t_vector			start;
	t_vector			vector;
	double				radius;
	t_vector			capses[2];
	double				c_distances[2];
	int					c_color[2];
}						t_icylinder;

typedef struct			s_triangle
{
	t_vector			points[3];
	t_vector			normale;
}						t_triangle;

typedef struct			s_squard
{
	t_vector			position;
	t_vector			rotation;
	double				scale[2];
	t_vector			points[4];
	t_vector			normale;
}						t_squard;

typedef struct			s_cube
{
	t_vector			position;
	t_vector			rotation;
	t_vector			scale;
	t_squard			planes[6];
}						t_cube;

typedef struct			s_elipsoid
{
	t_vector			position;
	t_vector			rotation;
	double				radius;
	double				rdistance;
}						t_elipsoid;

typedef struct			s_figure
{
	void				*figure;
	int					color;
	float				reflection;
	int					mirror;
	int					texture;
	double				refract;
	t_figure_type		type;
	struct s_figure		*next;
}						t_figure;

typedef struct			s_space
{
	t_figure			*figures;
	t_light				*lights;
	t_ray				*cam;
	t_cl_figure			*cl_figures;
	t_cl_light			*cl_lights;
	t_cl_figure			*cl_figtmp;
	t_cl_light			*cl_ligtmp;

	int					antialiasing;
	int					sepia;
	int					cartoon;
	int					grayscale;
	int					inversion;
}						t_space;

typedef	struct			s_lrt
{
	t_light				*light;
	t_vector			intersection;
	t_vector			normale;
	t_vector			vlight;
	t_ray				*buf;
	double				bright;
	double				reflected;
	double				nl_s;
}						t_lrt;

typedef struct			s_view
{
	int					exit_loop;
	size_t				figures_num;
	size_t				lights_num;
	SDL_Window			*win[4];
	SDL_Event			event;
	SDL_Surface			*win_surface;
	unsigned int		*buff;
	t_gui				rr;
	t_select			select;
	t_list_obj			l_obj;
	t_sp_prop			prop;
	t_ic_prop			ic;
	t_pl_prop			pl;
	t_trial_prop		tri;
	t_cone_prop			con;
	t_cube_prop			cub;
	t_quad_prop			qua;
	t_elips_prop		elp;
	t_par_prop			par;
	t_light_prop		lp;
	t_amblight_prop		am;
	t_direct_prop		dir;
	unsigned int		*array;
	t_list_light		l_light;
	t_space				*space;
	t_slider			**sl;
	t_opencl			cl;
	t_ok				*ok;
	int					flag;
	struct sockaddr_in	addr;
	int					socket;
	int					server_client;
	int					sock_for_connect;
	char				*server_ip;
}						t_view;

void					copy_plane(t_cl_figure *figure, t_figure *tmp);
void					copy_sphere(t_cl_figure *figure, t_figure *tmp);
void					copy_cylinder(t_cl_figure *figure, t_figure *tmp);
void					copy_cone(t_cl_figure *figure, t_figure *tmp);
void					copy_cube(t_cl_figure *figure, t_figure *tmp);
void					copy_triangle(t_cl_figure *figure, t_figure *tmp);
void					copy_quadrate(t_cl_figure *figure, t_figure *tmp);
void					copy_elipsoid(t_cl_figure *figure, t_figure *tmp);
void					copy_paraboloid(t_cl_figure *figure, t_figure *tmp);
void					color_effects(t_view *view);
unsigned int			*checkerboard(void);
unsigned int			*perlin_noise(void);
unsigned int			*normal_disruption(t_view *view);
int						exit_x(t_view *view);
void					opencl_init(t_view *v);
void					opencl_init2(t_view *v);
void					opencl_errors(cl_int result, const char *msg);
void					cl_info(t_view *v);
void					cl_releasing(t_view *v);
void					cl_set_arg(t_view *v, void *arg, size_t arg_size,
																cl_uint id);
void					cl_set_mem_arg(t_view *v, void *arg, size_t arg_size,
																cl_uint id);
void					set_arguments(t_view *v);
void					init_cam(t_view *v, cl_float3 *cam_o, cl_float3 *cam_v);
t_cl_light				*copy_light(t_view *v);
t_cl_figure				*copy_figures(t_view *v);
cl_float3				copy_vector(t_vector vector);
double					rt_lightr(t_vector l, t_vector normale,
										t_vector view, t_vector buf);
t_lrt					tlrt_init(t_space *space, t_ray *ray,
										t_figure *figure, double k);
int						do_lightrt(t_space *space, t_ray *ray,
										t_figure *figure, double k);
int						rt(t_space *space, t_ray *ray);
void					do_rt(t_view *view);
void					add_light(t_light *light, t_view *view);
void					add_figure(t_figure *figure, t_view *view);
t_vector				get_intersection(t_ray *ray, double k);
void					space_init(const char *filename, t_view *view);
void					cam_rotate(t_ray *ray, t_vector vector);
double					*find_cube_sqrt(double a, double b, double c, double d);
void					rotate_x(t_vector *ps, double l);
void					rotate_y(t_vector *ps, double l);
void					rotate_z(t_vector *ps, double l);
void					rotate_p_cl_z(cl_float3 *dot_rot,
							cl_float3 *dot_null, float angle);
void					rotate_p_cl_x(cl_float3 *dot_rot,
							cl_float3 *dot_null, float angle);
void					rotate_p_cl_y(cl_float3 *dot_rot,
							cl_float3 *dot_null, float angle);
void					rotate_cl_x(cl_float3 *ps, float l);
void					rotate_cl_y(cl_float3 *ps, float l);
void					rotate_cl_z(cl_float3 *ps, float l);
cl_float3				mult_vec_cl(cl_float3 v, float k);
cl_float3				sub_vec_cl(cl_float3 v1, cl_float3 v2);
cl_float3				sum_vec_cl(cl_float3 v1, cl_float3 v2);
cl_float3				vector_cl_init(float x, float y, float z);
cl_float3				choose_vec(int id);
t_vector				vector_init(double x, double y, double z);
double					vscalar_multiple(t_vector a, t_vector b);
t_vector				vk_multiple(t_vector vector, double k);
int						vis_equal(t_vector vector1, t_vector vector2);
t_vector				get_default_vector(char ch);
t_vector				vmultiple(t_vector a, t_vector b);
t_vector				vsum(t_vector a, t_vector b);
t_vector				vsub(t_vector a, t_vector b);
double					vlen(t_vector a);
t_vector				vnormalize(t_vector a);
int						check_hex(const char *str);
int						ft_hexatoi(const char *str);
void					parse_scene(const char *filename, t_view *view);
void					parse_cam(JSON_Object *root, t_view *view);
void					parse_cone(JSON_Object *cone, t_view *view);
void					parse_cube(JSON_Object *cube, t_view *view);
void					parse_cylinder(JSON_Object *cylinder, t_view *view);
void					parse_plane(JSON_Object *plane, t_view *view);
void					parse_sphere(JSON_Object *sphere, t_view *view);
int						check_array(JSON_Array *array, JSON_Value_Type type,
																size_t len);
int						check_triangle_points(t_vector vector[3]);
void					parse_triangle(JSON_Object *triangle, t_view *view);
void					parse_elipsoid(JSON_Object *elipsoid, t_view *view);
void					parse_paraboloid(JSON_Object *paraboloid, t_view *view);
t_figure				*init_parab(t_figure *fparaboloid,
							t_vector v1, t_vector v2);
void					parse_quadrate(JSON_Object *quadrate, t_view *view);
int						check_quadr_points(t_vector vector[5]);
t_squard				*calc_quadrate_params(t_squard *q);
void					root_parse_error(t_view *view);
void					parse_point(JSON_Object *light, t_view *view);
void					parse_ambient(JSON_Object *light, t_view *view);
void					parse_directional(JSON_Object *light, t_view *view);
t_vector				parse_vector(JSON_Array *vector, t_vector def);
void					parse_color_reflection(JSON_Object *sphere,
															t_figure *figure);
void					parse_effects(JSON_Object *root, t_view *view);
void					check_parse(JSON_Object *figure,
							t_view *view, char *type);
t_light					*light_init(char type,
							t_vector o, t_vector d, double inten);
double					check_cone_intersection(t_ray *ray, t_icone *cone);
t_vector				get_cone_normale(t_vector p, t_icone *cone);
t_figure				*cone_init(t_ray *axis, double k, int color,
															double reflection);
t_figure				*cube_init(t_vector vector[3], int color,
															double reflection);
t_figure				*quadrate_init(t_vector rotation,
							t_vector position, double scale[2]);
void					count_planes(t_cube *cube);
double					check_cylinder_intersection(t_ray *ray,
														t_icylinder *cylinder);
t_vector				get_cylinder_normale(t_vector p, t_icylinder *cylinder);
t_figure				*cylinder_init(t_ray *axis, double radius, int color,
															double reflection);
t_ray					*ray_init(t_vector origin, t_vector vector);
t_vector				get_normale(t_vector ray, t_figure *f);
double					check_intersection(t_ray *ray, t_figure *figure);
int						check_intersections(t_ray *ray, t_figure *figures);
double					check_plane_intersection(t_ray *ray, t_iplane *plane);
t_vector				get_plane_normale(t_iplane *plane);
t_figure				*plane_init(t_vector normale, t_vector point, int color,
															double reflection);
double					get_sqr_solve(double a, double b, double d);
double					check_sphere_intersection(t_ray *ray, t_sphere *figure);
t_vector				get_sphere_normale(t_vector p, t_sphere *f);
t_figure				*sphere_init(t_vector center, double r, int color,
															double reflection);
t_vector				count_triangle_normale(t_vector a[3]);
t_figure				*triangle_init(t_vector point[3], int color,
															double reflection);
t_figure				*elipsoid_init(t_vector position, t_vector rotation,
												int color, double reflection);
int						set_brightness(int color, double brightness,
														double bbrightness);
void					server_init(t_view	*view);
void					server_send_get_info(t_view *view);
void					client_init(t_view *view);
void					client_send_get_info(t_view *view);
bool					recv_all(int socket, void *buffer, size_t length);
bool					send_all(int socket, void *buffer, size_t length);
void					pack(unsigned char *buff, t_view *view);
void					unpack(unsigned char *buff, t_view *view);
void					fill_half_scr(unsigned int *half_scr, t_view *view);
void					serialize_char(unsigned char **buffer, char value);
void					serialize_int(unsigned char **buffer, int value);
void					serialize_double(unsigned char **buffer, double value);
char					deserialize_char(unsigned char **buffer);
int						deserialize_int(unsigned char **buffer);
double					deserialize_double(unsigned char **buffer);
char					*get_file_content(const char *const filename);
void					check_server(t_view *view, const char *const filename);
void					check_client(t_view *view, const char *const filename);
void					usage(t_view *view, int argc, char **argv);
void					initing_mode(t_view *view, const char *const filename);
void					choose_mode(t_view *view);

#endif
