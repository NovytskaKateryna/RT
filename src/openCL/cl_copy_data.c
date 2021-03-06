/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_copy_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:43:52 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/10 20:37:32 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

typedef void	(*t_copy)(t_cl_figure*, t_figure*);

static t_copy	*copy_array(void)
{
	t_copy	*copy;

	copy = (t_copy*)malloc(sizeof(t_copy) * 9);
	copy[InfinitePlane] = &copy_plane;
	copy[Sphere] = &copy_sphere;
	copy[InfiniteCylinder] = &copy_cylinder;
	copy[InfiniteCone] = &copy_cone;
	copy[Triangle] = &copy_triangle;
	copy[Cube] = &copy_cube;
	copy[Quadrate] = &copy_quadrate;
	copy[Elipsoid] = &copy_elipsoid;
	copy[Parabaloid] = &copy_paraboloid;
	return (copy);
}

void			init_cam(t_view *v, cl_float3 *cam_o, cl_float3 *cam_v)
{
	cam_o->x = v->space->cam->o.x;
	cam_o->y = v->space->cam->o.y;
	cam_o->z = v->space->cam->o.z;
	cam_v->x = v->space->cam->v.x;
	cam_v->y = v->space->cam->v.y;
	cam_v->z = v->space->cam->v.z;
}

t_cl_light		*copy_light(t_view *v)
{
	t_cl_light	*light;
	t_light		*tmp;
	int			n;

	tmp = v->space->lights;
	light = (t_cl_light*)malloc(sizeof(t_cl_light) * v->lights_num);
	n = 0;
	while (tmp)
	{
		light[n].origin.x = tmp->o.x;
		light[n].origin.y = tmp->o.y;
		light[n].origin.z = tmp->o.z;
		light[n].inten = tmp->inten;
		light[n].direction = copy_vector(tmp->d);
		light[n].type = tmp->type;
		tmp = tmp->next;
		n++;
	}
	return (light);
}

cl_float3		copy_vector(t_vector vector)
{
	cl_float3	copy;

	copy.x = vector.x;
	copy.y = vector.y;
	copy.z = vector.z;
	return (copy);
}

t_cl_figure		*copy_figures(t_view *v)
{
	static t_copy	*copy_figure = NULL;
	t_cl_figure		*figures;
	t_figure		*tmp;
	int				n;

	if (copy_figure == NULL)
		copy_figure = copy_array();
	tmp = v->space->figures;
	figures = (t_cl_figure*)ft_memalloc(sizeof(t_cl_figure) * v->figures_num);
	n = 0;
	while (tmp)
	{
		figures[n].type = tmp->type;
		figures[n].color = tmp->color;
		figures[n].reflection = tmp->reflection;
		figures[n].mirror = tmp->mirror;
		figures[n].texture = tmp->texture;
		figures[n].refract = tmp->refract;
		copy_figure[tmp->type](&figures[n], tmp);
		tmp = tmp->next;
		n++;
	}
	return (figures);
}
