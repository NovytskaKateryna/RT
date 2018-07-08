/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 19:41:22 by vvinogra          #+#    #+#             */
/*   Updated: 2018/06/11 23:06:11 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "effects.h"

static void		fill_square_help(t_checkboard *c, unsigned int *texture)
{
	int y;
	int x;

	y = c->y * (256 / c->ch_size);
	while (y < (c->y + 1) * (256 / c->ch_size))
	{
		x = c->x * (256 / c->ch_size);
		while (x < (c->x + 1) * (256 / c->ch_size))
		{
			if (c->x % 2 == c->y % 2)
				texture[y * 256 + x] = 0;
			else
				texture[y * 256 + x] = 0xffffff;
			x++;
		}
		y++;
	}
}

static void		checkerboard_fill(t_checkboard *c, unsigned int *texture)
{
	c->y = 0;
	while (c->y < c->ch_size)
	{
		c->x = 0;
		while (c->x < c->ch_size)
		{
			fill_square_help(c, texture);
			c->x++;
		}
		c->y++;
	}
}

unsigned int	*checkerboard(void)
{
	unsigned int	*texture;
	t_checkboard	c;

	srand(time(0));
	texture = (unsigned int*)malloc(sizeof(unsigned int) * (256 * 256));
	if (!texture)
		exit(EXIT_FAILURE);
	c.ch_size = pow(4, (rand() % 3 + 1));
	checkerboard_fill(&c, texture);
	return (texture);
}
