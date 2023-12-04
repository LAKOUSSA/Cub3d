/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:30:06 by gloukas           #+#    #+#             */
/*   Updated: 2023/11/29 10:56:59 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	my_mlx_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	render_player(t_mlx *game)
{
	int	x;
	int	y;
	int	color;
	int	tile_size;

	tile_size = 8;
	x = game->player.pos_x / TILE_SIZE * tile_size;
	y = game->player.pos_y / TILE_SIZE * tile_size;
	color = 0xFF0000;
	my_mlx_put_pixel(&(game->img), x, y, color);
}

void	render_map_chunk(t_mlx *game, int x_offset, int y_offset)
{
	int	x;
	int	y;
	int	color;
	int	tile_size;

	x = x_offset;
	y = y_offset;
	tile_size = 8;
	while (y < y_offset + tile_size)
	{
		x = x_offset;
		while (x < x_offset + tile_size)
		{
			if (game->map[y / tile_size][x / tile_size] == '1')
			{
				color = 0x808080;
				if (x % 2)
					my_mlx_put_pixel(&(game->img), x, y,
						color);
			}
			x++;
		}
		y++;
	}
}

void	render_map(t_mlx *game)
{
	int	x_offset;
	int	y_offset;
	int	tile_size;
	int	width;
	int	height;

	x_offset = 0;
	y_offset = 0;
	tile_size = 8;
	width = get_max_len(game->map) * tile_size;
	height = ft_array_length(game->map) * tile_size;
	while (y_offset < height)
	{
		x_offset = 0;
		while (x_offset < width)
		{
			render_map_chunk(game, x_offset, y_offset);
			x_offset += tile_size;
		}
		y_offset += tile_size;
	}
}
