/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:10:12 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:10:13 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(mlx_image_t *img, uint32_t ceiling, uint32_t floor)
{
	int	width;
	int	height;
	int	half_height;
	int	x;
	int	y;

	width = img->width;
	height = img->height;
	half_height = height / 2;
	x = -1;
	y = -1;
	while (++y < half_height)
	{
		x = -1;
		while (++x < width)
			safe_put_pixel(img, x, y, ceiling);
	}
	y = half_height - 1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			safe_put_pixel(img, x, y, floor);
	}
}
