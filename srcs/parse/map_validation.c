/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:11:25 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:11:42 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_map_data(t_map *map)
{
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_path = NULL;
	map->f_color = 1;
	map->c_color = 1;
	map->map_grid = NULL;
	map->max_r = 0;
	map->max_c = 0;
	map->start_pos_c = -1;
	map->start_pos_r = -1;
	map->direction = -1;
}

int	map_validation(t_map *map, int fd, char *file)
{
	char	**map_file;

	init_map_data(map);
	map_file = read_map_file(fd, file);
	if (!map_file)
		return (EXIT_FAILURE);
	if (get_map_content(map, map_file, -1) == EXIT_FAILURE)
	{
		ft_free_grid((void **)map_file);
		return (EXIT_FAILURE);
	}
	ft_free_grid((void **)map_file);
	return (EXIT_SUCCESS);
}
