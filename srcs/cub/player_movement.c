/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:10:35 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:10:36 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_forward_backward(t_cub *cub, int direction)
{
	double	move_x;
	double	move_y;
	double	new_x;
	double	new_y;

	move_x = cos(cub->player.angle) * MOVE_SPEED * direction;
	move_y = sin(cub->player.angle) * MOVE_SPEED * direction;
	new_x = cub->player.p_x + move_x;
	new_y = cub->player.p_y + move_y;
	if (is_valid_position(cub, new_x, cub->player.p_y))
		cub->player.p_x = new_x;
	if (is_valid_position(cub, cub->player.p_x, new_y))
		cub->player.p_y = new_y;
}

static void	move_left_right(t_cub *cub, int direction)
{
	double	move_x;
	double	move_y;
	double	new_x;
	double	new_y;

	move_x = sin(cub->player.angle) * MOVE_SPEED * direction;
	move_y = -cos(cub->player.angle) * MOVE_SPEED * direction;
	new_x = cub->player.p_x + move_x;
	new_y = cub->player.p_y + move_y;
	if (is_valid_position(cub, new_x, cub->player.p_y))
		cub->player.p_x = new_x;
	if (is_valid_position(cub, cub->player.p_x, new_y))
		cub->player.p_y = new_y;
}

static void	rotate_player(t_cub *cub, int direction)
{
	cub->player.angle += ROT_SPEED * direction;
	cub->player.angle = normalize_angle(cub->player.angle);
}

void	update_player_position(t_cub *cub)
{
	cub->pos_x = cub->player.p_x * TILE + TILE / 2.0;
	cub->pos_y = cub->player.p_y * TILE + TILE / 2.0;
}

void	player_movement(mlx_key_data_t keydata, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_hook_handle(cub);
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_forward_backward(cub, 1);
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_forward_backward(cub, -1);
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_left_right(cub, 1);
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		move_left_right(cub, -1);
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		rotate_player(cub, -1);
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		rotate_player(cub, 1);
	update_player_position(cub);
}
