/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:12:04 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:12:05 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_element_value(t_map *map, char *value, int ele_type)
{
	if (ele_type == NO)
		map->no_path = ft_strdup(value);
	else if (ele_type == SO)
		map->so_path = ft_strdup(value);
	else if (ele_type == WE)
		map->we_path = ft_strdup(value);
	else if (ele_type == EA)
		map->ea_path = ft_strdup(value);
}

int	validate_image(t_map *map, char **line_splited, int e_type)
{
	int				fd;
	int				len;
	unsigned char	header[8];

	if (!line_splited[1][0] || check_str_whitespaces(line_splited[1]))
		return (parse_error(map, line_splited, "No path found\n"), 1);
	len = ft_strlen(line_splited[1]);
	if (len < 5 || ft_strncmp(line_splited[1] + len - 4, ".png", 4) != 0)
		return (parse_error(map, line_splited, "Not a .png image\n"), 1);
	if (access(line_splited[1], F_OK) == -1)
		return (parse_error(map, line_splited, "Invalid access\n"), 1);
	fd = open(line_splited[1], O_RDONLY);
	if (fd == -1)
		return (parse_error(map, line_splited, "File open failed\n"), 1);
	if (read(fd, header, 8) != 8 || header[0] != 0x89 || header[1] != 0x50
		|| header[2] != 0x4E || header[3] != 0x47 || header[4] != 0x0D
		|| header[5] != 0x0A || header[6] != 0x1A || header[7] != 0x0A)
	{
		close(fd);
		return (parse_error(map, line_splited, "Invalid .png signature\n"), 1);
	}
	close(fd);
	set_element_value(map, line_splited[1], e_type);
	return (EXIT_SUCCESS);
}

int	get_numeric_value(char *str)
{
	int	nbr;

	if (!str[0])
		return (-1);
	if (*str == '0')
	{
		while (*str == '0')
			str++;
		nbr = 0;
	}
	if (ft_strlen(str) > 3)
		return (-1);
	nbr = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		nbr = nbr * 10 + *str++ - '0';
	}
	if (nbr > 255)
		return (-1);
	return (nbr);
}

unsigned int	set_color_value(t_map *map, char **line, char **color_grid)
{
	unsigned int	color;
	int				red;
	int				green;
	int				blue;

	red = get_numeric_value(color_grid[0]);
	green = get_numeric_value(color_grid[1]);
	blue = get_numeric_value(color_grid[2]);
	if (red == -1 || green == -1 || blue == -1)
		return (parse_error(map, line, "Invalid RGB color value\n"), 1);
	color = (red << 24) + (green << 16) + (blue << 8) + 255;
	return (color);
}

int	validate_color(t_map *map, char **line_splited, int e_type)
{
	char			**color_grid;
	int				rows;
	unsigned int	color_value;

	color_value = 1;
	if (color_comma_count(line_splited[1]) != 2)
		return (parse_error(map, line_splited, "Invalid color format\n"), 1);
	color_grid = ft_split(line_splited[1], ',');
	if (!color_grid)
		return (parse_error(map, line_splited, "Color grid split failed\n"), 1);
	rows = ft_grid_rows(color_grid);
	if (rows != 3)
	{
		ft_free_grid((void **)color_grid);
		return (parse_error(map, line_splited, "Invalid RGB format\n"), 1);
	}
	color_value = set_color_value(map, line_splited, color_grid);
	ft_free_grid((void **)color_grid);
	if (color_value == 1)
		return (EXIT_FAILURE);
	if (e_type == F)
		map->f_color = color_value;
	else
		map->c_color = color_value;
	return (EXIT_SUCCESS);
}
