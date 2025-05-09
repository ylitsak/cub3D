/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:10:42 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:10:43 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	init_rays_and_position(t_cub *cub, t_raycast *rays, int x)
{
	double	ray_offset;

	ray_offset = ((double)x / WIDTH) * FOV;
	rays->ray_angle = normalize_angle(cub->player.angle - (FOV / 2.0)
			+ ray_offset);
	rays->ray_dir_x = cos(rays->ray_angle);
	rays->ray_dir_y = sin(rays->ray_angle);
	cub->tile_x = cub->pos_x / TILE;
	cub->tile_y = cub->pos_y / TILE;
	cub->map_x = (int)(cub->pos_x / TILE);
	cub->map_y = (int)(cub->pos_y / TILE);
}

void	correct_fisheye_view(t_cub *cub, t_raycast *rays)
{
	double	cos_angle_diff;

	cos_angle_diff = cos(normalize_angle(rays->ray_angle - cub->player.angle));
	rays->wall_dist *= cos_angle_diff;
}

double	get_texture_position(t_cub *cub, t_raycast *rays, int side)
{
	int		line_height;
	double	hit_position;
	double	ray_distance;
	double	step_offset;

	line_height = (int)(rays->screen_dist * TILE / rays->wall_dist);
	cub->wall_top = HEIGHT / 2 - line_height / 2;
	cub->wall_bottom = HEIGHT / 2 + line_height / 2;
	if (side == 0)
	{
		step_offset = (1 - rays->step_x) / 2.0;
		ray_distance = (cub->map_x - cub->tile_x + step_offset)
			/ rays->ray_dir_x;
		hit_position = cub->tile_y + ray_distance * rays->ray_dir_y;
	}
	else
	{
		step_offset = (1 - rays->step_y) / 2.0;
		ray_distance = (cub->map_y - cub->tile_y + step_offset)
			/ rays->ray_dir_y;
		hit_position = cub->tile_x + ray_distance * rays->ray_dir_x;
	}
	hit_position = hit_position - floor(hit_position);
	return (hit_position);
}

mlx_image_t	*get_wall_textures(t_cub *cub, t_raycast *rays, int side)
{
	if (side == 1)
	{
		if (rays->ray_dir_y > 0)
			return (cub->image->south);
		else
			return (cub->image->north);
	}
	if (rays->ray_dir_x < 0)
		return (cub->image->west);
	else
		return (cub->image->east);
}
