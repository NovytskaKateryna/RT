/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 18:39:39 by ataranov          #+#    #+#             */
/*   Updated: 2018/06/12 18:43:35 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_light		*light_init(char type, t_vector o, t_vector d, double inten)
{
	t_light *new_light;

	new_light = (t_light*)malloc(sizeof(t_light));
	new_light->type = type;
	new_light->o = o;
	new_light->d = d;
	new_light->inten = inten;
	new_light->next = NULL;
	return (new_light);
}
