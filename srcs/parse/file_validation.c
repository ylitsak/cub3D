/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:11:15 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:11:16 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	file_error(int fd, char *file_name, char *err_msg)
{
	if (fd > 2)
		close(fd);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}

int	file_validation(char *file)
{
	int	len;
	int	fd;

	if (file[0] == '\0' || check_white_spaces(file))
		file_error(0, file, " scene file not found\n");
	len = ft_strlen(file);
	if (len <= 4 || (len > 4 && file[len - 5] == '/'))
		file_error(0, file, " is an invalid file type\n");
	if (file[len - 4] != '.' || file[len - 3] != 'c' || file[len - 2] != 'u'
		|| file[len - 1] != 'b')
		file_error(0, file, " is an invalid file type\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		file_error(fd, file, " file error\n");
	return (fd);
}
