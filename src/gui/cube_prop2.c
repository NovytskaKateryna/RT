/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_prop2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 10:34:03 by arudenko          #+#    #+#             */
/*   Updated: 2018/06/10 10:34:05 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cube_prop3(t_view *s)
{
	s->cub.cu_rect[7] = make_rect(10, 550, 60, 32);
	s->cub.cu_tex[7] = create_text(s, "Mirror", 2, 32);
	s->cub.cu_pr_rect[7] = make_rect(120, 550, 60, 32);
	s->cub.cu_pr[7] = tf(s, 0, 2, 32);
	s->cub.cu_rect[8] = make_rect(10, 600, 100, 32);
	s->cub.cu_tex[8] = create_text(s, "Texture-id", 2, 32);
	s->cub.cu_pr_rect[8] = make_rect(120, 600, 60, 32);
	s->cub.cu_pr[8] = tf(s, 0, 2, 32);
	s->cub.cu_rect[9] = make_rect(10, 650, 90, 32);
	s->cub.cu_tex[9] = create_text(s, "Refraction", 2, 32);
	s->cub.cu_pr_rect[9] = make_rect(120, 650, 60, 32);
	s->cub.cu_pr[9] = tf(s, 0, 2, 32);
}
