/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:09:48 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:09:49 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_images(t_cub *cub)
{
	if (cub->image->north)
		mlx_delete_image(cub->mlx, cub->image->north);
	if (cub->image->south)
		mlx_delete_image(cub->mlx, cub->image->south);
	if (cub->image->east)
		mlx_delete_image(cub->mlx, cub->image->east);
	if (cub->image->west)
		mlx_delete_image(cub->mlx, cub->image->west);
	free(cub->image);
	cub->image = NULL;
}

void	cub_close(t_cub *cub, int exit_code)
{
	if (!cub)
		return ;
	if (cub->map)
		parse_free_clean(cub->map);
	if (cub->rays)
	{
		free(cub->rays);
		cub->rays = NULL;
	}
	if (cub->image)
		free_images(cub);
	if (cub->mlx)
		mlx_terminate(cub->mlx);
	exit (exit_code);
}

void	cub_error(t_cub *cub, char *err_msg, int exit_code)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(err_msg, 2);
	cub_close(cub, exit_code);
}

void	close_hook_handle(void *param)
{
	cub_close((t_cub *)param, EXIT_SUCCESS);
}
