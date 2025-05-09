/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:11:48 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:11:49 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	str_free_null(char **cmd_str)
{
	if (*cmd_str)
	{
		free(*cmd_str);
		*cmd_str = NULL;
	}
}

void	parse_free_clean(t_map *map)
{
	if (!map)
		return ;
	if (map->no_path)
		str_free_null(&map->no_path);
	if (map->so_path)
		str_free_null(&map->so_path);
	if (map->we_path)
		str_free_null(&map->we_path);
	if (map->ea_path)
		str_free_null(&map->ea_path);
	if (map->map_grid)
		ft_free_grid((void **)map->map_grid);
}

void	parse_error(t_map *map, char **grid, char *err_msg)
{
	if (map)
		parse_free_clean(map);
	if (grid)
		ft_free_grid((void **)grid);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(err_msg, 2);
}
