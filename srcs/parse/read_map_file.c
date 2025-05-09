/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:11:59 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:12:00 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	read_error(char **map_file, char *err_msg, int fd)
{
	if (map_file)
		ft_free_grid((void **)map_file);
	if (fd > 2)
		close(fd);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(err_msg, 2);
}

static char	**get_map_file_content(int fd, char **map_file)
{
	char	*read_line;
	int		i;

	i = 0;
	read_line = NULL;
	read_line = ft_line_reader(fd, read_line, BUFFER_SIZE, 0);
	while (read_line)
	{
		map_file[i] = ft_strtrim(read_line, "\n");
		if (!map_file[i])
		{
			free(read_line);
			return (read_error(map_file, "Map reading failed 1\n", fd), NULL);
		}
		free(read_line);
		read_line = NULL;
		read_line = ft_line_reader(fd, read_line, BUFFER_SIZE, 0);
		i++;
	}
	map_file[i] = NULL;
	free(read_line);
	read_line = NULL;
	return (map_file);
}

static int	check_empty_content(char **map_file, int rows)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < rows)
	{
		if (!map_file[i][0] || check_str_whitespaces(map_file[i]))
			count++;
		i++;
	}
	if (count == rows)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	**read_map_file(int fd, char *file)
{
	int		rows;
	char	*read_line;
	char	**map_file;

	read_line = NULL;
	rows = map_file_row_count(file, read_line);
	if (rows == 0)
		return (read_error(NULL, "Map file is empty\n", fd), NULL);
	map_file = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!map_file)
		return (read_error(NULL, "Map memory allocation failed\n", fd), NULL);
	map_file = get_map_file_content(fd, map_file);
	if (!map_file)
		return (read_error(NULL, "Map file reading failed\n", fd), NULL);
	if (check_empty_content(map_file, rows))
		return (read_error(map_file, "Map file has no content\n", fd), NULL);
	close(fd);
	return (map_file);
}
