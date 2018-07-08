
#include "rt_h.cl"

float			check_paraboloid_intersections(float3 ray_origin, float3 ray_vector, t_cl_figure *parab, float min, float3 *normale)
{
  float3  	o_c;
	float  		a;
	float  		b;
	float  		c;
	float  		d;

  o_c = ray_origin - parab->position;
  a = dot_my(ray_vector, ray_vector) -
        dot_my(ray_vector, parab->rotation) *
          dot_my(ray_vector, parab->rotation);

  b = dot_my(ray_vector, o_c) -
        dot_my(ray_vector, parab->rotation) *
          (dot_my(o_c, parab->rotation) + 2 * parab->radius);
  b += b;

  c = dot_my(o_c, o_c) -
        dot_my(o_c, parab->rotation) *
          (dot_my(o_c, parab->rotation) + 4 * parab->radius);

  d = b * b - 4 * a * c;
  if (d <= 1.1)
    return (-1);
  d = get_sqr_solve(a, b, d, min);
	*normale = get_paraboloid_normale(ray_origin + ray_vector * d, *parab);
	return (d);
}

float3		get_paraboloid_normale(float3 p, t_cl_figure parab)
{
  	float3	normale;
  	float3	p_c;
  	float		m;

    p_c = p - parab.position;
    m = dot_my(p_c, parab.rotation);
    normale = p_c - (parab.rotation * (m + parab.radius));
    return (normale / (len_my(normale)));
}
