/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:11:53 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:11:54 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_element(t_map_ele ele_type)
{
	if (ele_type == NO || ele_type == SO || ele_type == WE || ele_type == EA
		|| ele_type == F || ele_type == C)
		return (1);
	return (0);
}

int	get_map_element_type(char **line_ele)
{
	if (line_ele && line_ele[0] == NULL)
		return (-1);
	else if (!ft_strcmp(line_ele[0], "NO"))
		return (NO);
	else if (!ft_strcmp(line_ele[0], "SO"))
		return (SO);
	else if (!ft_strcmp(line_ele[0], "WE"))
		return (WE);
	else if (!ft_strcmp(line_ele[0], "EA"))
		return (EA);
	else if (!ft_strcmp(line_ele[0], "F"))
		return (F);
	else if (!ft_strcmp(line_ele[0], "C"))
		return (C);
	else
		return (NONE);
}

int	map_file_row_count(char *file_path, char *read_line)
{
	int	rows;
	int	fd;

	rows = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		file_error(fd, file_path, " file error while counting map rows\n");
	read_line = ft_line_reader(fd, read_line, BUFFER_SIZE, 0);
	while (read_line)
	{
		rows++;
		free(read_line);
		read_line = NULL;
		read_line = ft_line_reader(fd, read_line, BUFFER_SIZE, 0);
	}
	close(fd);
	if (read_line)
	{
		free(read_line);
		read_line = NULL;
	}
	return (rows);
}

int	color_comma_count(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == ',')
			count++;
		str++;
	}
	return (count);
}

int	check_str_whitespaces(char *input_str)
{
	while (*input_str != '\0')
	{
		if (*input_str < 9 || *input_str > 13)
			return (0);
		input_str++;
	}
	return (1);
}
