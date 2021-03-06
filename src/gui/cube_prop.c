/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_prop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:27:28 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/21 14:27:32 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline void	cube_prop2(t_view *s)
{
	s->cub.cu_rect[4] = make_rect(80, 400, 110, 32);
	s->cub.cu_tex[4] = create_text(s, "Rotation-X", 2, 32);
	s->cub.cu_pr_rect[4] = make_rect(80, 400, 110, 32);
	s->cub.cu_pr[4] = NULL;
	s->cub.cu_rect[5] = make_rect(80, 450, 110, 32);
	s->cub.cu_tex[5] = create_text(s, "Rotation-Y", 2, 32);
	s->cub.cu_pr_rect[5] = make_rect(80, 450, 110, 32);
	s->cub.cu_pr[5] = NULL;
	s->cub.cu_rect[6] = make_rect(80, 500, 110, 32);
	s->cub.cu_tex[6] = create_text(s, "Rotation-Z", 2, 32);
	s->cub.cu_pr_rect[6] = make_rect(80, 500, 110, 32);
	s->cub.cu_pr[6] = NULL;
}

void				cube_prop(t_view *s)
{
	s->cub.cu_tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_CU_PR);
	s->cub.cu_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_CU_PR);
	s->cub.cu_pr_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_CU_PR);
	s->cub.cu_pr = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_CU_PR);
	s->cub.cu_rect[0] = make_rect(10, 200, 100, 32);
	s->cub.cu_tex[0] = create_text(s, "Position-X", 2, 32);
	s->cub.cu_pr_rect[0] = make_rect(120, 200, 60, 32);
	s->cub.cu_pr[0] = tf(s, 0, 2, 32);
	s->cub.cu_rect[1] = make_rect(10, 250, 100, 32);
	s->cub.cu_tex[1] = create_text(s, "Position-Y", 2, 32);
	s->cub.cu_pr_rect[1] = make_rect(120, 250, 60, 32);
	s->cub.cu_pr[1] = tf(s, 0, 2, 32);
	s->cub.cu_rect[2] = make_rect(10, 300, 100, 32);
	s->cub.cu_tex[2] = create_text(s, "Position-Z", 2, 32);
	s->cub.cu_pr_rect[2] = make_rect(120, 300, 60, 32);
	s->cub.cu_pr[2] = tf(s, 0, 2, 32);
	s->cub.cu_rect[3] = make_rect(10, 350, 100, 32);
	s->cub.cu_tex[3] = create_text(s, "Reflection", 2, 32);
	s->cub.cu_pr_rect[3] = make_rect(120, 350, 60, 32);
	s->cub.cu_pr[3] = tf(s, 0, 2, 32);
	cube_prop2(s);
	cube_prop3(s);
}

void				init_cube_prop(t_view *s)
{
	t_col	c;

	c = col_parse(s->space->cl_figures[s->rr.fl.y].color);
	s->sl[0]->slider_rect.x = c.red;
	s->sl[0]->clr.red = s->sl[0]->slider_rect.x;
	s->sl[1]->slider_rect.x = c.green;
	s->sl[1]->clr.green = s->sl[1]->slider_rect.x;
	s->sl[2]->slider_rect.x = c.blue;
	s->sl[2]->clr.blue = s->sl[2]->slider_rect.x;
	s->cub.cu_pr[0] = tf(s,
		s->space->cl_figures[s->rr.fl.y].position.x, 2, 32);
	s->cub.cu_pr[1] = tf(s,
		s->space->cl_figures[s->rr.fl.y].position.y, 2, 32);
	s->cub.cu_pr[2] = tf(s,
		s->space->cl_figures[s->rr.fl.y].position.z, 2, 32);
	s->cub.cu_pr[3] = tf(s,
		s->space->cl_figures[s->rr.fl.y].reflection, 2, 32);
	s->cub.cu_pr[5] = NULL;
	s->cub.cu_pr[6] = NULL;
	s->cub.cu_pr[7] = tf(s, s->space->cl_figures[s->rr.fl.y].mirror, 2, 32);
	s->cub.cu_pr[8] = tf(s, s->space->cl_figures[s->rr.fl.y].texture, 2, 32);
	s->cub.cu_pr[9] = tf(s, s->space->cl_figures[s->rr.fl.y].refract, 2, 32);
}

void				print_cube_prop(t_view *s)
{
	int i;

	i = -1;
	SDL_RenderClear(s->rr.rend[2]);
	while (++i < NUM_CU_PR && s->flag == 0)
	{
		SDL_RenderCopy(s->rr.rend[2], s->cub.cu_tex[i],
			NULL, &s->cub.cu_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->cub.cu_pr[i],
			NULL, &s->cub.cu_pr_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->ok->b_ok, NULL, &s->ok->ok_rect);
		display_colored_rect(s);
	}
	SDL_SetRenderDrawColor(s->rr.rend[2], 10, 20, 40, 255);
	SDL_RenderPresent(s->rr.rend[2]);
}

void				clean_cube_prop(t_view *s)
{
	int	i;

	i = -1;
	while (++i < NUM_CU_PR)
	{
		if (s->cub.cu_tex[i])
		{
			SDL_DestroyTexture(s->cub.cu_tex[i]);
			s->cub.cu_tex[i] = NULL;
		}
		if (s->cub.cu_pr[i])
		{
			SDL_DestroyTexture(s->cub.cu_pr[i]);
			s->cub.cu_pr[i] = NULL;
		}
	}
}
