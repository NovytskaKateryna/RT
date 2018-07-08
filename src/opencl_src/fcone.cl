
#include "rt_h.cl"


void			swaps_arr(float *inter_dists)
{
	float buf;

	buf = inter_dists[0];
	inter_dists[0] = inter_dists[1];
	inter_dists[1] = buf;
}


float			check_cone_intersection1(float3 ray_origin, float3 ray_vector, t_cl_figure cone, float *inter_dists, float min)
{
	float a;
	float b;
	float c;
	float d;
	float3 or_ver;

	or_ver = ray_origin - cone.vertex;
	a = dot_my(ray_vector, ray_vector) - ((1 + pow_my(cone.radius, 2)) *
			(pow_my(dot_my(ray_vector, cone.vector), 2)));
	b = 2 * (dot_my(ray_vector, or_ver) - ((1 + pow_my(cone.radius, 2)) *
			dot_my(ray_vector, cone.vector) * dot_my(or_ver, cone.vector)));
	c = dot_my(or_ver, or_ver) - ((1 + pow_my(cone.radius, 2)) *
			(pow_my(dot_my(or_ver, cone.vector), 2)));
	d = pow_my(b, 2) - 4 * a * c;
	if (d < 0)
		return (d);
	d = q_rsqrt(d);
	inter_dists[0] = (-b + d ) / (2.0f * a);
	inter_dists[1] = (-b - d ) / (2.0f * a);
	if (inter_dists[0] < min && inter_dists[1] < min)
		return (-1);
	if (inter_dists[1] >= min)
	{
		if (inter_dists[0] < min || inter_dists[0] > inter_dists[1])
			swaps_arr(inter_dists);
	}
	return (1);
}

float			check_cone_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure *cone, float min, float3 *normale)
{
	float	inter_dists_cone[2];

	cone->normale = (float3){0, 0, 0};
	if (check_cone_intersection1(ray_origin, ray_vector, *cone, inter_dists_cone, min) < 0)
		return (-1);
	*normale = get_cone_normale(ray_origin + ray_vector * inter_dists_cone[0], *cone);
	return (inter_dists_cone[0]);
}

float3		get_cone_normale(float3 p, t_cl_figure cone)
{
	float		m;
	float3	res;

	if (cone.normale.x == 0 && cone.normale.y == 0 && cone.normale.z == 0)
	{
		m = pow_my(len_my(subtraction(p, cone.vertex)), 2) / dot_my(subtraction(p,
				cone.vertex), cone.vector);
		res = sum(cone.vertex, k_multiply(cone.vector, m));
		res = fast_normalize(subtraction(p, res));
		return (res);
	}
	return (cone.normale);
}
