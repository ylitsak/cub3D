/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:10:04 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:10:05 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_image_t	*texture_process(t_cub *cub, char *path)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	tex = mlx_load_png(path);
	if (!tex)
		cub_error(cub, "Texture load failed\n", EXIT_FAILURE);
	img = mlx_texture_to_image(cub->mlx, tex);
	mlx_delete_texture(tex);
	if (!img)
		cub_error(cub, "Image create failed\n", EXIT_FAILURE);
	return (img);
}

static void	load_textures(t_cub *cub)
{
	cub->image = ft_calloc(1, sizeof * cub->image);
	if (!cub->image)
		cub_error(cub, "Image malloc failed\n", EXIT_FAILURE);
	cub->image->north = texture_process(cub, cub->map->no_path);
	cub->image->south = texture_process(cub, cub->map->so_path);
	cub->image->east = texture_process(cub, cub->map->ea_path);
	cub->image->west = texture_process(cub, cub->map->we_path);
}

static void	ray_loop(void *parameter)
{
	t_cub	*cub;

	cub = (t_cub *)parameter;
	raycasting(cub, cub->rays);
}

void	cub_start(t_cub *cub)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!cub->mlx)
		cub_error(cub, "mlx initiation failed\n", EXIT_FAILURE);
	cub->screen = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(cub->mlx, cub->screen, 0, 0);
	if (!cub->screen)
		cub_error(cub, "mlx screen image failed\n", EXIT_FAILURE);
	load_textures(cub);
	mlx_key_hook(cub->mlx, player_movement, cub);
	mlx_close_hook(cub->mlx, close_hook_handle, cub);
	mlx_loop_hook(cub->mlx, ray_loop, cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}
