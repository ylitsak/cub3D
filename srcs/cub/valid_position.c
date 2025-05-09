/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:10:55 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:10:56 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	collision_check(t_cub *cub, double px, double py)
{
	int	m_x;
	int	m_y;

	m_x = (int)(px / TILE);
	m_y = (int)(py / TILE);
	if (cub->map->map_grid[m_y][m_x] == '1')
		return (0);
	return (1);
}

int	is_valid_position(t_cub *cub, double tile_x, double tile_y)
{
	double	px;
	double	py;
	double	distance;

	px = tile_x * TILE + TILE / 2;
	py = tile_y * TILE + TILE / 2;
	distance = TILE * COLLISION_MARGIN;
	if (!collision_check(cub, px, py))
		return (0);
	if (!collision_check(cub, px + distance, py))
		return (0);
	if (!collision_check(cub, px - distance, py))
		return (0);
	if (!collision_check(cub, px, py + distance))
		return (0);
	if (!collision_check(cub, px, py - distance))
		return (0);
	return (1);
}
