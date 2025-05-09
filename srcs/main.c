/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:12:10 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:12:11 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_cub_data(t_cub *cub, t_map *map)
{
	cub->map = map;
	cub->rays = malloc(sizeof(t_raycast));
	if (!cub->rays)
		cub_error(cub, "malloc failed allocating raycast\n", EXIT_FAILURE);
	cub->mlx = NULL;
	cub->image = NULL;
	cub->player.p_x = map->start_pos_r;
	cub->player.p_y = map->start_pos_c;
	if (map->direction == 'N')
		cub->player.angle = N;
	else if (map->direction == 'S')
		cub->player.angle = S;
	else if (map->direction == 'W')
		cub->player.angle = W;
	else if (map->direction == 'E')
		cub->player.angle = E;
	cub->pos_x = cub->player.p_x * TILE + TILE / 2.0;
	cub->pos_y = cub->player.p_y * TILE + TILE / 2.0;
	cub->rays->screen_dist = (WIDTH / 2.0) / tan(FOV / 2.0);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_cub	cub;
	int		fd;

	if (argc != 2)
	{
		ft_putstr_fd("Error\n Wrong number of arguments\n", 2);
		return (1);
	}
	fd = file_validation(argv[1]);
	if (map_validation(&map, fd, argv[1]))
		exit(EXIT_FAILURE);
	ft_bzero(&cub, sizeof(cub));
	init_cub_data(&cub, &map);
	cub_start(&cub);
	cub_close(&cub, EXIT_SUCCESS);
}
