/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <kaoel-yo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:48:04 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/12/02 11:39:39 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_char(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->m[++i])
	{
		j = 0;
		while (data->m[i][j])
		{
			if (data->m[i][j] == 'N' || data->m[i][j] == 'E'
				|| data->m[i][j] == 'S' || data->m[i][j] == 'W')
			{
				data->nop++;
				data->fov = data->m[i][j];
				j++;
			}
			if (data->m[i][j] == ' ' || data->m[i][j] == '1'
				|| data->m[i][j] == '0' || data->m[i][j] == '\n')
				j++;
			else
				return (0);
		}
	}
	return (1);
}

int	check_characters(t_data *data)
{
	if (!check_char(data))
		print_error("Error\ninvalid map");
	if (data->nop != 1)
		return (0);
	return (1);
}

int	check_the_wall(t_data *data)
{
	int	j;
	int	i;

	i = -1;
	while (data->m[++i])
	{
		j = -1;
		while (data->m[i][++j])
		{
			if ((j == 0 && data->m[i][j] != '1' && data->m[i][j] != ' ')
				|| (i == 0 && data->m[i][j] != '1' && data->m[i][j] != ' ')
				|| (i == ft_array_length(data->m) - 1 && data->m[i][j] != '1'
					&& data->m[i][j] != ' '))
				return (0);
			else if (data->m[i][j] == '0' || data->m[i][j] == 'N'
				|| data->m[i][j] == 'E' || data->m[i][j] == 'S'
				|| data->m[i][j] == 'W')
				if (data->m[i][j + 1] == '\0' || data->m[i][j - 1] == ' '
					|| data->m[i][j + 1] == ' ' || data->m[i + 1][j] == ' '
					|| data->m[i - 1][j] == ' ')
					return (0);
		}
	}
	return (1);
}

int	is_map(char *str)
{
	int	i;

	i = 1;
	while (str[i] == ' ')
		i++;
	while (str[i] != '\n')
	{
		if (str[i] != '1' && str[i] != '0')
			return (0);
		else
			return (1);
		i++;
	}
	return (0);
}

void	check_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && is_map(str + i))
		{
			i++;
			break ;
		}
		i++;
	}
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
			print_error("Error\nsomthing is wrong");
		i++;
	}
}
