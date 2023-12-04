/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 09:03:18 by gloukas           #+#    #+#             */
/*   Updated: 2023/11/29 10:53:16 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

int	get_x_offset(t_ray *ray, int texture_width)
{
	int	texture_x;

	texture_x = (int)(ray->hit_x * texture_width / TILE_SIZE) % texture_width;
	if (ray->is_vertical)
		texture_x = (int)(ray->hit_y * texture_width / TILE_SIZE)
			% texture_width;
	if (ray->is_horizontal)
		texture_x = (int)(ray->hit_x * texture_width / TILE_SIZE)
			% texture_width;
	if (ray->is_vertical && ray->angle > PI)
		texture_x = texture_width - texture_x - 1;
	if (ray->is_horizontal && ray->angle >= PI / 2 && ray->angle <= 3 * PI / 2)
		texture_x = texture_width - texture_x - 1;
	return (texture_x);
}

int	set_textures_direction(t_ray *ray)
{
	if (ray->is_horizontal)
	{
		if (ray->angle >= 0 && ray->angle < PI)
			return (SOUTH);
		else
			return (NORTH);
	}
	else
	{
		if (ray->angle >= PI / 2 && ray->angle < 3 * PI / 2)
			return (WEST);
		else
			return (EAST);
	}
}

int	fill_texture(t_mlx *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->ptr, path, &(texture->width),
			&(texture->height));
	if (!(texture->img))
	{
		print_error("Error\nTexture file not found\n");
		return (-1);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	if (!(texture->addr))
	{
		print_error("Error\nTexture file not found\n");
		return (-1);
	}
	texture->width = 894;
	texture->height = 894;
	return (1);
}

int	init_textures(t_mlx *game)
{
	game->textures = malloc(sizeof(t_texture) * 4);
	if (!game->textures)
	{
		print_error("Error\nMalloc failed\n");
		return (-1);
	}
	ft_memset(game->textures, 0, sizeof(t_texture) * 4);
	if ((fill_texture(game, &(game->textures[0]), game->data->south) == -1)
		|| (fill_texture(game, &(game->textures[1]), game->data->north) == -1)
		|| (fill_texture(game, &(game->textures[2]), game->data->west) == -1)
		|| (fill_texture(game, &(game->textures[3]), game->data->east) == -1))
		return (-1);
	return (1);
}

void	draw_line(t_mlx *game, int x, t_index index, int color)
{
	int	y1;
	int	y2;

	y1 = index.y1;
	y2 = index.y2;
	while (y1 < y2)
	{
		my_mlx_put_pixel(&(game->img), x, y1, color);
		y1++;
	}
}
