/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:11:21 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:11:22 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**create_empty_map(int row, int col)
{
	char	**map_grid;
	int		i;

	map_grid = (char **)ft_calloc(row + 1, sizeof(char *));
	if (!map_grid)
		return (NULL);
	i = -1;
	while (++i < row)
	{
		map_grid[i] = (char *)ft_calloc(col + 1, sizeof(char));
		if (!map_grid[i])
		{
			ft_free_grid((void **)map_grid);
			return (NULL);
		}
		ft_memset(map_grid[i], ' ', col);
	}
	return (map_grid);
}

static char	**create_new_map_grid(t_map *map, char **map_grid, int add)
{
	int		row;
	int		col;
	char	**new_grid;

	new_grid = create_empty_map(map->max_r + 2 * add, map->max_c + 2 * add);
	if (!new_grid)
		return (parse_error(map, map_grid, "Map copying failed\n"), NULL);
	row = -1;
	while (map_grid && map_grid[++row])
	{
		col = -1;
		while (map_grid[row][++col])
			new_grid[row + add][col + add] = map_grid[row][col];
	}
	return (new_grid);
}

static int	map_visited_fill_in(t_map *map, char **temp_map, int row, int col)
{
	if (row < 0 || col < 0 || !temp_map[row] || !temp_map[row][col]
		|| temp_map[row][col] == ' ')
		return (1);
	if (temp_map[row][col] == '1')
		return (0);
	temp_map[row][col] = '1';
	return (map_visited_fill_in(map, temp_map, row + 1, col)
		|| map_visited_fill_in(map, temp_map, row - 1, col)
		|| map_visited_fill_in(map, temp_map, row, col + 1)
		|| map_visited_fill_in(map, temp_map, row, col - 1));
}

static int	map_visited_fill_out(t_map *map, char **temp_map, int row, int col)
{
	if (row < 0 || col < 0 || !temp_map[row] || !temp_map[row][col]
		|| temp_map[row][col] == '1')
		return (0);
	if (temp_map[row][col] == '0')
		return (1);
	temp_map[row][col] = '1';
	return (map_visited_fill_out(map, temp_map, row + 1, col)
		|| map_visited_fill_out(map, temp_map, row - 1, col)
		|| map_visited_fill_out(map, temp_map, row, col + 1)
		|| map_visited_fill_out(map, temp_map, row, col - 1));
}

int	object_path_validation(t_map *map, char **map_grid)
{
	char	**temp_map;

	temp_map = create_new_map_grid(map, map_grid, 1);
	if (!temp_map)
		return (parse_error(map, map_grid, "Temp map copy failed\n"), 1);
	if (map_visited_fill_in(map, temp_map, map->start_pos_c + 1,
			map->start_pos_r + 1) || map_visited_fill_out(map, temp_map, 0, 0))
	{
		ft_free_grid((void **)temp_map);
		return (parse_error(map, map_grid, "Map is not surrounded by wall\n"),
			1);
	}
	ft_free_grid((void **)temp_map);
	ft_free_grid((void **)map->map_grid);
	map->map_grid = create_new_map_grid(map, map_grid, 0);
	ft_free_grid((void **)map_grid);
	return (EXIT_SUCCESS);
}
