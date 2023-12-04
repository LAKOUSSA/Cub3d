/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <kaoel-yo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:51:48 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/12/02 09:41:20 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

int	get_max_len(char **map)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = ft_strlen(map[i]);
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (max < len)
			max = len;
		i++;
	}
	return (max);
}

void	fill_map(char **map, t_data *data)
{
	int	i;
	int	j;
	int	max;

	data->m = malloc(sizeof(char *) * (ft_array_length(map) + 1));
	max = get_max_len(map);
	i = 0;
	while (i < ft_array_length(map))
	{
		data->m[i] = malloc(max + 1);
		j = 0;
		while (map[i][j])
		{
			data->m[i][j] = map[i][j];
			j++;
		}
		while (j < max)
		{
			data->m[i][j] = ' ';
			j++;
		}
		data->m[i][j] = '\0';
		i++;
	}
	data->m[i] = NULL;
}

void	get_player_position(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->m[++i])
	{
		j = -1;
		while (data->m[i][++j])
		{
			if (data->m[i][j] == 'N' || data->m[i][j] == 'S'
				|| data->m[i][j] == 'E' || data->m[i][j] == 'W')
			{
				data->pop_y = i;
				data->pop_x = j;
				return ;
			}
		}
	}
}

void	check_lines(t_data *data)
{
	char	*line;
	int		i;
	int		count;

	count = 0;
	i = -1;
	while (data->file1[++i])
	{
		line = ft_strtrim(data->file1[i], " ");
		if (line[0] == '1')
		{
			check_map(data->file1 + i, data);
			free(line);
			return ;
		}
		else if (!check_direction(line, data))
		{
			free(line);
			return ;
		}
		free(line);
		count++;
	}
	if (count >= 6)
		print_error("Error\nsomthing is wrong ...");
}

void	check_map(char **map, t_data *data)
{
	fill_map(map, data);
	get_player_position(data);
	if (!check_characters(data))
		print_error("Error\ninvalid map");
	if (!check_the_wall(data))
		print_error("Error\ncheck the map ");
	if (data->count != 6)
		print_error("Error\nsomthing is wrong .");
}
