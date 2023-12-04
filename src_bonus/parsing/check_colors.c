/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <kaoel-yo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:14:17 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/12/02 09:40:14 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

int	is_all_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	invalid_rgb(char **line)
{
	int		i;
	char	*c;

	i = 0;
	while (i < 3)
	{
		c = ft_strtrim(line[i], " ");
		if (ft_strlen(c) < 1 || ft_strlen(c) > 3 || !is_all_digits(c)
			|| ft_atoi(c) < 0 || ft_atoi(c) > 255)
		{
			free(c);
			return (1);
		}
		free(c);
		i++;
	}
	return (0);
}

int	invalid_cf_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ',' && line[i] != ' ' && !ft_isdigit(line[i]))
			return (1);
		i++;
	}
	return (0);
}

void	check_floor(char *line, t_data *data)
{
	int		i;
	char	**floor_rgb;

	i = 2;
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	floor_rgb = ft_split(line + i, ',');
	if (invalid_cf_line(line + i) || invalid_rgb(floor_rgb)
		|| ft_array_length(floor_rgb) != 3 || count_comma(line + i) != 2)
		print_error("Error\nf");
	if (data->floor_r != -1)
		print_error("Error\nf");
	data->floor_r = ft_atoi(floor_rgb[0]);
	data->floor_g = ft_atoi(floor_rgb[1]);
	data->floor_b = ft_atoi(floor_rgb[2]);
	data->count++;
	free_array(floor_rgb);
}

void	check_ceiling(char *line, t_data *data)
{
	int		i;
	char	**ceiling_rgb;

	i = 2;
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	ceiling_rgb = ft_split(line + i, ',');
	if (invalid_cf_line(line + i) || invalid_rgb(ceiling_rgb)
		|| ft_array_length(ceiling_rgb) != 3 || count_comma(line + i) != 2)
		print_error("Error\nc");
	if (data->ceiling_r != -1)
		print_error("Error\nc");
	data->ceiling_r = ft_atoi(ceiling_rgb[0]);
	data->ceiling_g = ft_atoi(ceiling_rgb[1]);
	data->ceiling_b = ft_atoi(ceiling_rgb[2]);
	data->count++;
	free_array(ceiling_rgb);
}
