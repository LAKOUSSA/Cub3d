/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaoel-yo <kaoel-yo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:22:51 by kaoel-yo          #+#    #+#             */
/*   Updated: 2023/11/28 12:53:15 by kaoel-yo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_init_data(t_data *data)
{
	data->fov = 0;
	data->nop = 0;
	data->pop_x = 0;
	data->pop_y = 0;
	data->file1 = NULL;
	data->file = NULL;
	data->north = NULL;
	data->south = NULL;
	data->east = NULL;
	data->west = NULL;
	data->m = NULL;
	data->count = 0;
	data->floor_r = -1;
	data->floor_g = -1;
	data->floor_b = -1;
	data->ceiling_r = -1;
	data->ceiling_g = -1;
	data->ceiling_b = -1;
}
