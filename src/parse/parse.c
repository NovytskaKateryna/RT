/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 11:47:00 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/12 19:46:11 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			parse_figure(JSON_Object *figure, t_view *view)
{
	char	*type;

	if (!json_object_dothas_value_of_type(figure, "type", JSONString))
	{
		ft_putendl_fd("Unknown figure found. Skipped", STDERR_FILENO);
		return ;
	}
	type = (char*)json_object_get_string(figure, "type");
	check_parse(figure, view, type);
}

static void			parse_figures(JSON_Object *root, t_view *view)
{
	JSON_Array	*array;
	JSON_Object	*figure;
	size_t		i;

	if (json_object_dothas_value_of_type(root, "figures", JSONArray))
	{
		array = json_object_dotget_array(root, "figures");
		i = json_array_get_count(array);
		while (i > 0)
		{
			if ((figure = json_array_get_object(array, i - 1)) != NULL)
				parse_figure(figure, view);
			i--;
		}
	}
	else if (json_object_dothas_value_of_type(root, "figures", JSONObject))
		parse_figure(json_object_dotget_object(root, "figures"), view);
	else
		ft_putendl_fd("Figures field is not present. Please check your input.",
				STDERR_FILENO);
}

static void			parse_light(JSON_Object *light, t_view *view)
{
	char	*type;

	if (!(json_object_dothas_value_of_type(light, "type", JSONString)))
	{
		ft_putendl_fd("Unknown light found. Skipped", STDERR_FILENO);
		return ;
	}
	type = (char*)json_object_get_string(light, "type");
	if (ft_strequ(type, "ambient"))
		parse_ambient(light, view);
	else if (ft_strequ(type, "point"))
		parse_point(light, view);
	else if (ft_strequ(type, "direction"))
		parse_directional(light, view);
	else
		ft_putendl_fd("Unknown light found. Skipped", STDERR_FILENO);
}

static void			parse_lights(JSON_Object *root, t_view *view)
{
	JSON_Array	*array;
	JSON_Object	*figure;
	size_t		i;

	if (json_object_dothas_value_of_type(root, "lights", JSONArray))
	{
		array = json_object_dotget_array(root, "lights");
		i = json_array_get_count(array);
		while (i > 0)
		{
			if ((figure = json_array_get_object(array, i - 1)) != NULL)
				parse_light(figure, view);
			i--;
		}
	}
	else if (json_object_dothas_value_of_type(root, "lights", JSONObject))
		parse_light(json_object_dotget_object(root, "lights"), view);
}

void				parse_scene(const char *filename, t_view *view)
{
	JSON_Value		*root;
	JSON_Value_Type	type;
	JSON_Object		*root_obj;

	errno = 0;
	if (!(root = json_parse_file(filename)))
	{
		ft_putendl_fd("Cannot parse file", STDERR_FILENO);
		exit(1);
	}
	type = json_value_get_type(root);
	if (type != JSONObject)
		root_parse_error(view);
	root_obj = json_value_get_object(root);
	parse_figures(root_obj, view);
	parse_lights(root_obj, view);
	parse_cam(root_obj, view);
	parse_effects(root_obj, view);
	json_value_free(root);
	if (view->figures_num <= 0 || view->lights_num <= 0)
	{
		ft_putendl_fd("Cannot parse file", STDERR_FILENO);
		exit(1);
	}
}
