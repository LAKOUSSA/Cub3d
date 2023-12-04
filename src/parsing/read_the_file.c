/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_the_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <kaoel-yo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:12:24 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/12/02 09:27:19 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_arg(char **argv)
{
	int	i;

	i = 0;
	while (argv[1][i])
		i++;
	i -= 1;
	if (argv[1][i] == 'b' && argv[1][i - 1] == 'u' && argv[1][i - 2] == 'c'
		&& argv[1][i - 3] == '.' && argv[1][i - 4] != '/' && argv[1][i
		- 4] != 0)
		return (1);
	return (0);
}

char	*read_file(char **argv)
{
	int		fd;
	char	*line;
	char	*p;

	p = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		print_error("Error\nfile not found");
	line = get_next_line(fd);
	if (!line)
		print_error("Error\nfile is empty");
	while (line)
	{
		p = ft_strjoin(p, line);
		free(line);
		line = get_next_line(fd);
	}
	return (p);
}

int	check_input(int argc, char **argv)
{
	if (argc < 2)
	{
		print_error("Error\nNo map file provided\n");
		return (-1);
	}
	if (argc > 3)
	{
		print_error("Error\nToo many arguments\n");
		return (-1);
	}
	if (!check_arg(argv))
	{
		print_error("error\ninvalid file type!! use .cub");
		return (-1);
	}
	return (1);
}

t_data	*parsing(int argc, char **argv)
{
	t_data	*data;

	if (check_input(argc, argv) == -1)
		return (NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		return (free(data), NULL);
	ft_init_data(data);
	data->file = read_file(argv);
	check_new_line(data->file);
	data->file1 = ft_split(data->file, '\n');
	check_lines(data);
	return (data);
}
