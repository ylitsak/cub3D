/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:11:10 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:11:11 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	map_data_update(t_map *map, int i, int j, char directiion)
{
	map->start_pos_c = i;
	map->start_pos_r = j;
	map->direction = directiion;
}

static int	validate_map(t_map *map, char **map_grid, int i, int sign_count)
{
	int	col_c;
	int	j;

	if (!map_grid)
		return (EXIT_FAILURE);
	while (++i < map->max_r)
	{
		j = -1;
		col_c = ft_len_line(map_grid[i]);
		if (col_c < 1 || check_str_whitespaces(map_grid[i]))
			return (parse_error(map, map_grid, "Map has empty line\n"), 1);
		while (++j < col_c)
		{
			if (!ft_strchr("01NEWS ", map_grid[i][j]))
				return (parse_error(map, map_grid, "Invalid character\n"), 1);
			if (ft_strchr("NEWS", map_grid[i][j]))
			{
				sign_count++;
				map_data_update(map, i, j, map_grid[i][j]);
			}
		}
	}
	if (sign_count != 1)
		return (parse_error(map, map_grid, "Wrong direction in the map\n"), 1);
	return (EXIT_SUCCESS);
}

int	extract_map(t_map *map, char **map_file, int i)
{
	int		len;
	char	**map_grid;
	int		start;

	start = i;
	len = ft_grid_rows(map_file);
	map_grid = (char **)malloc(sizeof(char *) * (len - i + 1));
	if (!map_grid)
		return (parse_error(map, NULL, "Map memory allocation failed\n"), 1);
	while (i < len)
	{
		map_grid[i - start] = ft_strdup(map_file[i]);
		if (ft_strlen(map_file[i]) > map->max_c)
			map->max_c = ft_strlen(map_file[i]);
		if (!map_grid[i - start])
			return (parse_error(map, map_grid, "Map grid copy failed\n"), 1);
		i++;
	}
	map->max_r = i - start;
	map_grid[i - start] = NULL;
	if (validate_map(map, map_grid, -1, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (object_path_validation(map, map_grid))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
