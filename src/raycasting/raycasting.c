/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:31:55 by gloukas           #+#    #+#             */
/*   Updated: 2023/11/29 11:39:34 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	raycasting(t_mlx *game)
{
	int		i;
	t_ray	ray;

	game->ceiling_color = create_rgb(game->data->ceiling_r,
			game->data->ceiling_g, game->data->ceiling_b);
	game->floor_color = create_rgb(game->data->floor_r, game->data->floor_g,
			game->data->floor_b);
	ray.color = create_rgb(103, 51, 0);
	i = 0;
	ray.angle = fmod(game->player.fov - FOV / 2, 2 * PI);
	while (i < WI)
	{
		while (ray.angle < 0)
			ray.angle += 2 * PI;
		while (ray.angle > 2 * PI)
			ray.angle -= 2 * PI;
		horizontal_intersection(game, &ray);
		vertical_intersection(game, &ray);
		ray = get_distance(game, ray);
		draw_wall(game, &ray, WI - i - 1);
		ray.angle += FOV / WI;
		i++;
	}
}

void	draw_wall(t_mlx *game, t_ray *ray, int x)
{
	t_walls	wall;
	int		texture_id;
	t_index	index;

	wall.x = x;
	ray->dist *= cos(ray->angle - game->player.fov);
	wall.wall_height = round((TILE_SIZE / ray->dist) * ((WI / 2) / tan(FOV
					/ 2)));
	wall.wall_top = (HE - wall.wall_height) / 2;
	wall.wall_bottom = wall.wall_top + wall.wall_height;
	index.y1 = 0;
	index.y2 = wall.wall_top;
	draw_line(game, wall.x, index, game->ceiling_color);
	create_starfield(game, wall.x, 0, wall.wall_top);
	texture_id = set_textures_direction(ray);
	draw_texture(game, ray, wall, game->textures[texture_id]);
	index.y1 = wall.wall_bottom;
	index.y2 = HE;
	draw_line(game, wall.x, index, game->floor_color);
}

void	create_starfield(t_mlx *game, int x, int y1, int y2)
{
	int	color;

	while (y1 < y2)
	{
		if (rand() % 500 < 1)
		{
			color = create_rgb(77, 84, 154);
			my_mlx_put_pixel(&(game->img), x, y1, color);
		}
		y1++;
	}
}

int	get_pixel_color(t_texture texture, int x, int y)
{
	int	color;
	int	pixel;

	pixel = (y * texture.line_len + x * (texture.bpp / 8));
	color = *(int *)(texture.addr + pixel);
	return (color);
}

void	draw_texture(t_mlx *game, t_ray *ray, t_walls wall, t_texture texture)
{
	int	x;
	int	color;
	int	texture_x;
	int	texture_y;

	texture_x = get_x_offset(ray, texture.width);
	texture_y = (int)(ray->hit_y * texture.height / TILE_SIZE) % texture.height;
	x = wall.x;
	wall.walltp = wall.wall_top;
	if (wall.wall_top < 0)
		wall.wall_top = 0;
	while (wall.wall_top < wall.wall_bottom && wall.wall_top < HE)
	{
		texture_y = (int)((wall.wall_top - wall.walltp) / wall.wall_height
				* texture.height);
		color = get_pixel_color(texture, texture_x, texture_y);
		my_mlx_put_pixel(&(game->img), x, wall.wall_top, color);
		wall.wall_top++;
	}
}
