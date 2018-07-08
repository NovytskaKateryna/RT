
#include "rt_h.cl"

float			check_elipsoid_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure *elips, float min, float3 *normale)
{
  float   ac[2];
  float   r;
  float   a;
  float   b;
  float   c;
  float   d;
  float3  o_c;


  o_c = ray_origin - elips->position;
  r = elips->rdistance + 2 * elips->radius;
  r *= r;
  ac[0] = 2 * elips->rdistance * dot_my(ray_vector, elips->rotation);
  ac[1] = r + 2 * elips->rdistance *
    dot_my(o_c, elips->rotation) - elips->rdistance;
  a = 4 * r * dot_my(ray_vector, ray_vector) - ac[0] * ac[0];
  b = 4 * r * dot_my(ray_vector, o_c) - ac[0] * ac[1];
  b += b;
  c = 4 * r * dot_my(o_c, o_c) - ac[1] * ac[1];
  d = b * b - 4 * a * c;
  if (d < 0)
		return (d);
	d = get_sqr_solve(a, b, d, min);
	*normale = get_elipsoid_normale(ray_origin + ray_vector * d, *elips);
	return (d);
}


float3		get_elipsoid_normale(float3 p, t_cl_figure elips)
{
  float3  dot_center;
  float3  p_c;
  float3  normale;
  float   a;
  float   b;
  float   buf;

  buf = elips.rdistance / 2;
  dot_center = elips.rotation * buf;
  dot_center = elips.position + dot_center;

  p_c = p - dot_center;
  a = 2 * elips.radius + elips.rdistance;
  b = a * a - elips.rdistance * elips.rdistance;
  buf = (b / (a * a)) * dot_my(p_c, elips.rotation);
  normale = p_c - (elips.rotation * buf);
  return (normale / (len_my(normale)));
}
