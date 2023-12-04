/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <kaoel-yo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:10:25 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/12/02 10:27:50 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	check_north(char *line, t_data *data)
{
	int		fd;
	char	**no;

	no = ft_split(line, ' ');
	if (data->north || ft_array_length(no) != 2)
		print_error("Error\nno ");
	fd = open(no[1], O_RDONLY);
	if (fd == -1)
		print_error("Error\nfile not found");
	close(fd);
	data->north = ft_strdup(no[1]);
	data->count++;
	free_array(no);
}

void	check_south(char *line, t_data *data)
{
	int		fd;
	char	**so;

	so = ft_split(line, ' ');
	if (data->south || ft_array_length(so) != 2)
		print_error("Error\nso ");
	fd = open(so[1], O_RDONLY);
	if (fd == -1)
		print_error("Error\nfile not found");
	close(fd);
	data->south = ft_strdup(so[1]);
	data->count++;
	free_array(so);
}

void	check_west(char *line, t_data *data)
{
	int		fd;
	char	**we;

	we = ft_split(line, ' ');
	if (data->west || ft_array_length(we) != 2)
		print_error("Error\nwe ");
	fd = open(we[1], O_RDONLY);
	if (fd == -1)
		print_error("Error\nfile not found");
	close(fd);
	data->west = ft_strdup(we[1]);
	data->count++;
	free_array(we);
}

void	check_east(char *line, t_data *data)
{
	int		fd;
	char	**ea;

	ea = ft_split(line, ' ');
	if (data->east || ft_array_length(ea) != 2)
		print_error("Error\nea ");
	data->east = ft_strdup(ea[1]);
	fd = open(data->east, O_RDONLY);
	if (fd == -1)
		print_error("Error\nfile not found");
	close(fd);
	data->count++;
	free_array(ea);
}

int	check_direction(char *line, t_data *data)
{
	if (!ft_strncmp(line, "NO ", 3))
		check_north(line, data);
	else if (!ft_strncmp(line, "SO ", 3))
		check_south(line, data);
	else if (!ft_strncmp(line, "WE ", 3))
		check_west(line, data);
	else if (!ft_strncmp(line, "EA ", 3))
		check_east(line, data);
	else if (!ft_strncmp(line, "F ", 2))
		check_floor(line, data);
	else if (!ft_strncmp(line, "C ", 2))
		check_ceiling(line, data);
	else
	{
		print_error("Error\nsomthing is wrong!!");
		return (0);
	}
	return (1);
}
