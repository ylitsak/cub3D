/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:11:04 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:11:05 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_duplicate(t_map *map, t_map_ele ele_type)
{
	if (ele_type == NO && map->no_path)
		return (parse_error(map, NULL, "Duplicate 'NO' identifier\n"), 1);
	else if (ele_type == SO && map->so_path)
		return (parse_error(map, NULL, "Duplicate 'SO' identifier\n"), 1);
	else if (ele_type == WE && map->we_path)
		return (parse_error(map, NULL, "Duplicate 'WE' identifier\n"), 1);
	else if (ele_type == EA && map->ea_path)
		return (parse_error(map, NULL, "Duplicate 'EA' identifier\n"), 1);
	else if (ele_type == F && map->f_color != 1)
		return (parse_error(map, NULL, "Duplicate 'F' identifier\n"), 1);
	else if (ele_type == C && map->c_color != 1)
		return (parse_error(map, NULL, "Duplicate 'C' identifier\n"), 1);
	return (EXIT_SUCCESS);
}

static int	check_missing_element(t_map *map, char **line_splited)
{
	if (!map->no_path)
		return (parse_error(map, line_splited, "Element 'NO' is missing\n"), 1);
	else if (!map->so_path)
		return (parse_error(map, line_splited, "Element 'SO' is missing\n"), 1);
	else if (!map->we_path)
		return (parse_error(map, line_splited, "Element 'WE' is missing\n"), 1);
	else if (!map->ea_path)
		return (parse_error(map, line_splited, "Element 'EA' is missing\n"), 1);
	else if (map->f_color == 1)
		return (parse_error(map, line_splited, "Element 'F' is missing\n"), 1);
	else if (map->c_color == 1)
		return (parse_error(map, line_splited, "Element 'C' is missing\n"), 1);
	return (EXIT_SUCCESS);
}

static int	extract_element(t_map *map, char **line_splited, int e_type)
{
	int	len;

	len = ft_grid_rows(line_splited);
	if (len != 2)
		return (parse_error(map, line_splited, "Wrong element format\n"), 1);
	if (check_duplicate(map, e_type))
	{
		ft_free_grid((void **)line_splited);
		return (EXIT_FAILURE);
	}
	if (e_type == NO || e_type == SO || e_type == WE || e_type == EA)
	{
		if (validate_image(map, line_splited, e_type))
			return (EXIT_FAILURE);
		if ((e_type == NO && !map->no_path) || (e_type == SO && !map->so_path)
			|| (e_type == WE && !map->we_path) || (e_type == EA
				&& !map->ea_path))
			return (parse_error(map, line_splited, "Image parse failed\n"), 1);
	}
	else if (e_type == F || e_type == C)
	{
		if (validate_color(map, line_splited, e_type))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	extract_map_grid(t_map *map, char **map_file, char **line_sp, int i)
{
	if (line_sp[0][0] && !ft_strchr("01", line_sp[0][0]))
		return (parse_error(map, line_sp, "Invalid element format\n"), 1);
	else
	{
		if (check_missing_element(map, line_sp))
			return (EXIT_FAILURE);
		ft_free_grid((void **)line_sp);
		if (extract_map(map, map_file, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	get_map_content(t_map *map, char **map_file, int i)
{
	char	**line_splited;
	int		ele_type;

	while (map_file[++i])
	{
		line_splited = ft_split(map_file[i], ' ');
		if (!line_splited)
			return (parse_error(map, line_splited, "Map split failed\n"), 1);
		ele_type = get_map_element_type(line_splited);
		if (is_valid_element(ele_type))
		{
			if (extract_element(map, line_splited, ele_type))
				return (EXIT_FAILURE);
		}
		else if (ele_type == NONE)
		{
			if (extract_map_grid(map, map_file, line_splited, i))
				return (EXIT_FAILURE);
			break ;
		}
		ft_free_grid((void **)line_splited);
	}
	if (!map->map_grid)
		return (parse_error(map, NULL, "No map grid\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
