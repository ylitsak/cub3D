/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:09:15 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:09:18 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parse.h"

// libraries
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <math.h>

# define MOVE_SPEED 0.10
# define ROT_SPEED 0.050
# define COLLISION_MARGIN 0.2

# define TILE 40
# define PI 3.1415926535
# define WIDTH 1400
# define HEIGHT 1000
# define N 4.7123889803846895
# define W PI
# define E 6.283185307179586
# define S 1.5707963267948966
# define FOV 1.0471975512

// structs

typedef struct s_player
{
	double		p_x;
	double		p_y;
	double		angle;
}	t_player;

typedef struct s_image
{
	mlx_image_t	*north;
	mlx_image_t	*south;
	mlx_image_t	*east;
	mlx_image_t	*west;
}				t_image;

typedef struct s_raycast
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	ray_angle;
	double	screen_dist;
	double	wall_dist;
	int		step_x;
	int		step_y;
}	t_raycast;

typedef struct s_colors
{
	uint32_t	color;
	uint8_t		a;
	uint8_t		b;
	uint8_t		g;
	uint8_t		r;
}	t_colors;

typedef struct s_cub
{
	double		pos_x;
	double		pos_y;
	double		tile_x;
	double		tile_y;
	int			map_x;
	int			map_y;
	int			wall_top;
	int			wall_bottom;
	int			draw_start;
	int			draw_end;
	uint32_t	*tex_pixels;
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*screen;
	t_raycast	*rays;
	t_player	player;
	t_image		*image;
	t_colors	colors;
}	t_cub;

// CUB
void			cub_start(t_cub *cub);
void			player_movement(mlx_key_data_t keydata, void *param);
void			close_hook_handle(void *param);
int				is_valid_position(t_cub *cub, double tile_x, double tile_y);
void			draw_walls(t_cub *cub, int x, mlx_image_t *texture,
					double tex_x);
void			draw_floor_ceiling(mlx_image_t *img, uint32_t ceiling,
					uint32_t floor);
void			safe_put_pixel(mlx_image_t *img, int x, int y, uint32_t color);

// RAYCAST
void			raycasting(t_cub *cub, t_raycast *rays);

// UTILS
double			normalize_angle(double angle);
void			init_rays_and_position(t_cub *cub, t_raycast *rays, int x);
void			correct_fisheye_view(t_cub *cub, t_raycast *rays);
double			get_texture_position(t_cub *cub, t_raycast *rays, int side);
mlx_image_t		*get_wall_textures(t_cub *cub, t_raycast *rays, int side);

// ERROR
void			free_images(t_cub *cub);
void			cub_close(t_cub *cub, int exit_code);
void			cub_error(t_cub *cub, char *err_msg, int exit_code);

#endif
