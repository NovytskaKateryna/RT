#include "rt_h.cl"

unsigned int	texture_sphere(float3 normal, __global unsigned int *texture, t_cl_figure closest)
{
	t_color col;
	float		u;
	float		v;
	int x = 0;
	int y = 0;
	int	w,h, lol;
	int kek;

	w = 256;
	h = 256;
	kek = (256 * 256 ) * 4;
	switch (closest.texture )
	{
		case 1:
			lol = 0;
			break;
		case 2:
			lol = kek;
			break;
		case 3:
			lol = kek + kek;
			break;
		case 4:
			lol = 3 * kek;
			break;
		case 5:
			lol = 4 * kek;
			break;
		case 6:
			lol = 5 * kek;
			break;
		break;
	}
	u = 0.5f + atan2(normal.z, normal.x) / 3.1415f;
	v = 0.5f - asin(normal.y / 2.0f) / 3.1415f;
	x = (int)(w * u) % w;
	y = (int)(h * v) % h;
	col.color = getcolor(&texture[lol], x, y, w);
	return (col.color);
}

unsigned int	getcolor(__global unsigned int *texture, int x, int y, int w)
{
	return (texture[y * w + x]);
}



unsigned int	texture_plane(float3 p_c, __global unsigned int *texture, t_cl_figure plane)
{
	t_color col;
	int x = 0;
	int y = 0;
	float3 buf_u = (float3){0.0f, 0.0f, 0.0f};
	float3 buf_v;
	float		u;
	float		v;
	int	w,h, lol;
	int	kek;

	w = 256;
	h = 256;
	kek = (256 * 256 ) * 4;
	switch (plane.texture )
	{
		case 1:
			lol = 0;
			break;
		case 2:
			lol = kek;
			break;
		case 3:
			lol = kek * 2;
			break;
		case 4:
			lol = 3 * kek;
			break;
		case 5:
			lol = 4 * kek;
			break;
		case 6:
			lol = 5 * kek;
			break;
		break;
	}
	buf_u = cross_vec(plane.normale, (float3)(0.f, 1.f, 0.f));
	if (fabs(len_my(buf_u)) < 0.0001f)
		buf_u = cross_vec(plane.normale, (float3)(0.f, 0.f, 1.f));
	buf_v = cross_vec(plane.normale, buf_u);

	u = dot_my(buf_u, p_c);
	v = dot_my(buf_v, p_c);

	x = (int)(w * u / 4) % w;
	y = (int)(h * v / 4) % h;
	if (x < 0)
		x += w;
	if (y < 0)
		y += h;
	col.color = getcolor(&texture[lol], x, y, w);
	return (col.color);
}

unsigned int	texture_cone(float3 p_c, float3 normal, __global unsigned int *texture, t_cl_figure closest)
{
	t_color col;
	float		u;
	float		v;
	int x = 0;
	int y = 0;
	int	w,h, lol;
	int	kek;

	w = 256;
	h = 256;
	kek = (256 * 256 ) * 4;
	float3 uu = closest.vector;
	float3 vec = closest.vertex - p_c;
	switch (closest.texture )
	{
		case 1:
			lol = 0;
			break;
		case 2:
			lol = (256 * 256 ) * 4;
			break;
		case 3:
			lol = (256 * 256 ) * 4 + (256 * 256 ) * 4;
			break;
		case 4:
			lol = 3 * kek;
			break;
		case 5:
			lol = 4 * kek;
			break;
		case 6:
			lol = 5 * kek;
			break;
		break;
	}
	u = fabs(dot_my(vec, (float3)(0,0,1)));
	v = dot(uu, vec);
	x = (int)(w * u) % w;
	y = (int)(h * v) % h;
	if (x < 0)
		x += w;
	if (y < 0)
		y += h;
	col.color = getcolor(&texture[lol], x, y, w);
	return (col.color);
}

unsigned int	global_texture(float3 normal, __global unsigned int *texture, t_cl_figure closest,
		float len, float3 ray_origin, float3 ray_vector)
{
	switch (closest.type)
	{
		case Sphere :
			return (texture_sphere(normal, texture, closest));
		case InfinitePlane :
		{
			float3 p = ray_origin + (ray_vector * len);
			return (texture_plane(closest.point - p, texture, closest));
		}
		case InfiniteCone:
		{
			float3 p = ray_origin + (ray_vector * len);
			return (texture_cone(closest.point - p, normal, texture, closest));
		}
		case InfiniteCylinder:
		{
			float3 p = ray_origin + (ray_vector * len);
			return (texture_cone(closest.point - p, normal, texture, closest));
		}
		case Cube :
		{
			float3 p = ray_origin + (ray_vector * len);
			return (texture_plane(closest.point - p, texture, closest));
		}
		case Quadrate :
		{
			float3 p = ray_origin + (ray_vector * len);
			return (texture_plane(closest.point - p, texture, closest));
		}
		break;
	}
	return (0);
}