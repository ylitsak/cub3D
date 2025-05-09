/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:10:21 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:10:22 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_wall_draw_limit(t_cub *cub)
{
	int	y;

	if (cub->wall_top < 0)
		cub->draw_start = 0;
	else
		cub->draw_start = cub->wall_top;
	if (cub->wall_bottom >= HEIGHT)
		cub->draw_end = HEIGHT - 1;
	else
		cub->draw_end = cub->wall_bottom;
	y = cub->draw_start;
	return (y);
}

static uint32_t	correct_colors(uint32_t *tex_pixels, int tex_pos, t_cub *cub)
{
	uint32_t	color_pix;
	uint32_t	corrected;

	color_pix = tex_pixels[tex_pos];
	cub->colors.a = (color_pix >> 24) & 0xFF;
	cub->colors.b = (color_pix >> 16) & 0xFF;
	cub->colors.g = (color_pix >> 8) & 0xFF;
	cub->colors.r = (color_pix >> 0) & 0xFF;
	corrected = (cub->colors.r << 24) | (cub->colors.g << 16)
		| (cub->colors.b << 8) | cub->colors.a;
	return (corrected);
}

void	safe_put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
		mlx_put_pixel(img, x, y, color);
}

void	draw_walls(t_cub *cub, int x, mlx_image_t *texture, double wall_tex_x)
{
	int			line_height;
	int			y;
	double		scale;
	uint32_t	wall_texture_y;
	int			texture_pos;

	line_height = cub->wall_bottom - cub->wall_top;
	if (line_height <= 0)
		return ;
	cub->tex_pixels = (uint32_t *)texture->pixels;
	y = set_wall_draw_limit(cub);
	while (y <= cub->draw_end)
	{
		scale = (double)(y - cub->wall_top) / line_height;
		wall_texture_y = (uint32_t)(scale * texture->height);
		if (wall_texture_y >= texture->height)
			wall_texture_y = texture->height - 1;
		texture_pos = wall_texture_y * texture->width + (int)wall_tex_x;
		cub->colors.color = correct_colors(cub->tex_pixels, texture_pos, cub);
		safe_put_pixel(cub->screen, x, y, cub->colors.color);
		y++;
	}
}
