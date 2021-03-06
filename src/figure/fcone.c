/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcone.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 18:39:39 by ataranov          #+#    #+#             */
/*   Updated: 2018/06/12 18:44:25 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			check_cone_intersection(t_ray *ray, t_icone *cone)
{
	double a;
	double b;
	double c;
	double d;

	a = vscalar_multiple(ray->v, ray->v) -
			((1 + pow(cone->radius, 2)) *
			(pow(vscalar_multiple(ray->v, cone->vector), 2)));
	b = 2 * (vscalar_multiple(ray->v, vsub(ray->o, cone->vertex)) -
			((1 + pow(cone->radius, 2)) *
			vscalar_multiple(ray->v, cone->vector) *
			vscalar_multiple(vsub(ray->o, cone->vertex), cone->vector)));
	c = vscalar_multiple(vsub(ray->o, cone->vertex),
			vsub(ray->o, cone->vertex)) -
			((1 + pow(cone->radius, 2)) *
			(pow(vscalar_multiple(vsub(ray->o, cone->vertex),
					cone->vector), 2)));
	d = pow(b, 2) - 4 * a * c;
	return (get_sqr_solve(a, b, d));
}

t_vector		get_cone_normale(t_vector p, t_icone *cone)
{
	double		m;
	t_vector	res;

	m = pow(vlen(vsub(p, cone->vertex)), 2) / vscalar_multiple(vsub(p,
			cone->vertex), cone->vector);
	res = vsum(cone->vertex, vk_multiple(cone->vector, m));
	res = vnormalize(vsub(p, res));
	return (res);
}

t_figure		*cone_init(t_ray *axis, double k, int color,
		double reflection)
{
	t_figure	*new_figure;
	t_icone		*cone;

	new_figure = (t_figure*)ft_memalloc(sizeof(t_figure));
	new_figure->type = InfiniteCone;
	cone = (t_icone*)ft_memalloc(sizeof(t_icone));
	cone->vertex = axis->o;
	cone->radius = k;
	new_figure->color = color;
	new_figure->reflection = reflection;
	cone->vector = vnormalize(axis->v);
	free(axis);
	new_figure->figure = cone;
	new_figure->next = NULL;
	return (new_figure);
}
