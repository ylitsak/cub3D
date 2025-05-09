/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shachowd <shachowd@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:09:30 by shachowd          #+#    #+#             */
/*   Updated: 2025/05/07 15:09:31 by shachowd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdint.h>
# include <stdio.h>

typedef struct s_cub	t_cub;

// data structures
typedef enum s_map_ele
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	NONE,
}						t_map_ele;

typedef struct s_map
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	uint32_t	f_color;
	uint32_t	c_color;
	char		**map_grid;
	int			max_r;
	int			max_c;
	int			start_pos_c;
	int			start_pos_r;
	char		direction;
}	t_map;

////....FUNCTION.....//
void		file_error(int fd, char *file_name, char *err_msg);
int			file_validation(char *file);
int			map_validation(t_map *map_d, int fd, char *file);
char		**read_map_file(int fd, char *file);
int			get_map_content(t_map *map, char **map_file, int i);
int			extract_map(t_map *map, char **map_file, int i);
int			validate_image(t_map *map, char **line_splited, int e_type);
int			validate_color(t_map *map, char **line_splited, int e_type);
int			object_path_validation(t_map *map, char **map_grid);

//.....ERROR....///
void		parse_error(t_map *map, char **grid, char *err_msg);
void		parse_free_clean(t_map *map);

//......UTILS.....//
int			is_valid_element(t_map_ele ele_type);
int			get_map_element_type(char **line_ele);
int			map_file_row_count(char *file_path, char *read_line);
int			color_comma_count(char *str);
int			check_str_whitespaces(char *input_str);
void		str_free_null(char **cmd_str);

/////TESTER////////
void		map_print(char **map);

#endif
