/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:10:49 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/08 11:05:12 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_grid_distance(t_raycast *rays)
{
	if (rays->ray_dir_x == 0)
		rays->delta_dist_x = 1e30;
	else
		rays->delta_dist_x = fabs(1.0 / rays->ray_dir_x);
	if (rays->ray_dir_y == 0)
		rays->delta_dist_y = 1e30;
	else
		rays->delta_dist_y = fabs(1.0 / rays->ray_dir_y);
	if (rays->ray_dir_x < 0)
		rays->step_x = -1;
	else
		rays->step_x = 1;
	if (rays->ray_dir_y < 0)
		rays->step_y = -1;
	else
		rays->step_y = 1;
}

static void	first_grid_hit(t_cub *cub, t_raycast *rays)
{
	if (rays->ray_dir_x < 0)
		rays->side_dist_x = (cub->tile_x - cub->map_x) * rays->delta_dist_x;
	else
		rays->side_dist_x = (cub->map_x + 1 - cub->tile_x) * rays->delta_dist_x;
	if (rays->ray_dir_y < 0)
		rays->side_dist_y = (cub->tile_y - cub->map_y) * rays->delta_dist_y;
	else
		rays->side_dist_y = (cub->map_y + 1 - cub->tile_y) * rays->delta_dist_y;
}

static int	raycast_to_wall(t_cub *cub, t_raycast *rays)
{
	int	hit;
	int	side;

	hit = 0;
	side = 0;
	while (hit == 0)
	{
		if (rays->side_dist_x < rays->side_dist_y)
		{
			rays->side_dist_x += rays->delta_dist_x;
			cub->map_x += rays->step_x;
			side = 0;
		}
		else
		{
			rays->side_dist_y += rays->delta_dist_y;
			cub->map_y += rays->step_y;
			side = 1;
		}
		if (cub->map->map_grid[cub->map_y][cub->map_x] == '1')
			hit = 1;
	}
	return (side);
}

static void	calculate_distance_to_wall(t_raycast *rays, int side)
{
	if (side == 0)
		rays->wall_dist = (rays->side_dist_x - rays->delta_dist_x) * TILE;
	else
		rays->wall_dist = (rays->side_dist_y - rays->delta_dist_y) * TILE;
}

void	raycasting(t_cub *cub, t_raycast *rays)
{
	int			x;
	int			side;
	double		hit_position;
	int			wall_texture_col;
	mlx_image_t	*wall_img;

	x = -1;
	draw_floor_ceiling(cub->screen, cub->map->c_color, cub->map->f_color);
	while (++x < WIDTH)
	{
		init_rays_and_position(cub, rays, x);
		calculate_grid_distance(rays);
		first_grid_hit(cub, rays);
		side = raycast_to_wall(cub, rays);
		calculate_distance_to_wall(rays, side);
		correct_fisheye_view(cub, rays);
		hit_position = get_texture_position(cub, rays, side);
		wall_img = get_wall_textures(cub, rays, side);
		wall_texture_col = (int)(hit_position * wall_img->width);
		if ((side == 0 && rays->ray_dir_x < 0) || (side == 1
				&& rays->ray_dir_y > 0))
			wall_texture_col = wall_img->width - wall_texture_col - 1;
		draw_walls(cub, x, wall_img, wall_texture_col);
	}
}
