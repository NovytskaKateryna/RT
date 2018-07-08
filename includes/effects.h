/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:51:33 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/11 23:02:46 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EFFECTS_H
# define EFFECTS_H

# include "rt.h"

# define X 0
# define Y 1

typedef struct		s_perlin
{
	unsigned int	*perlin_texture;
	t_color			color_t;
	double			p_factor;
	int				unit[3];
	double			location[3];
	double			faded[3];
	int				hashed[8];
	double			p[2];
	double			frequency;
	double			amplitude;
	double			octaves;
	double			persistence;
}					t_perlin;

typedef struct		s_checkboard
{
	int	ch_size;
	int	x;
	int y;
}					t_checkboard;

double				perlin2(int *hashed, double *faded, double *f);
double				fade(double t);
void				hash(int *p, int *unit, int *hashed);

#endif
