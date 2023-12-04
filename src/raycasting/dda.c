/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:20:01 by gloukas           #+#    #+#             */
/*   Updated: 2023/12/01 10:29:10 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_ray	*help_horizontal(t_mlx *game, t_ray *ray, double *x, double *y)
{
	if (ray->angle >= 0 && ray->angle < PI)
		ray->h_y = ((int)(game->player.pos_y / TILE_SIZE)) * TILE_SIZE;
	if (ray->angle >= 0 && ray->angle < PI)
		*y = -TILE_SIZE;
	if (ray->angle >= PI && ray->angle < 2 * PI)
		ray->h_y = ((int)(game->player.pos_y / TILE_SIZE)) * TILE_SIZE
			+ TILE_SIZE;
	if (ray->angle >= PI && ray->angle < 2 * PI)
		*y = TILE_SIZE;
	ray->h_x = game->player.pos_x + (game->player.pos_y - ray->h_y)
		/ tan(ray->angle);
	*x = TILE_SIZE / tan(ray->angle);
	if (sin(ray->angle) < 0)
		*x = -TILE_SIZE / tan(ray->angle);
	return (ray);
}

void	horizontal_intersection(t_mlx *game, t_ray *ray)
{
	double	x;
	double	y;

	ray = help_horizontal(game, ray, &x, &y);
	if (ray->h_x < 0 || ray->h_x >= game->width || ray->h_y < 0
		|| ray->h_y >= game->height)
		return ;
	while (1)
	{
		if (ray->h_x <= 0 || ray->h_x >= game->width || ray->h_y <= 0
			|| ray->h_y >= game->height)
			break ;
		if (game->map[(int)(ray->h_y / TILE_SIZE)] && game->map[(int)(ray->h_y
				/ TILE_SIZE)][(int)(ray->h_x / TILE_SIZE)]
			&& game->map[(int)(ray->h_y / TILE_SIZE)][(int)(ray->h_x
				/ TILE_SIZE)] == '1')
			break ;
		if (game->map[(int)((ray->h_y - 1) / TILE_SIZE)]
			&& game->map[(int)((ray->h_y - 1) / TILE_SIZE)][(int)(ray->h_x
				/ TILE_SIZE)] && game->map[(int)((ray->h_y - 1)
				/ TILE_SIZE)][(int)(ray->h_x / TILE_SIZE)] == '1')
			break ;
		ray->h_x += x;
		ray->h_y += y;
	}
}

t_ray	*help_vertical(t_mlx *game, t_ray *ray, double *x, double *y)
{
	ray->v_x = ((int)(game->player.pos_x / TILE_SIZE)) * TILE_SIZE
		+ TILE_SIZE;
	*x = TILE_SIZE;
	if (ray->angle >= PI / 2 && ray->angle <= 3 * PI / 2)
		ray->v_x = ((int)(game->player.pos_x / TILE_SIZE)) * TILE_SIZE;
	if (ray->angle >= PI / 2 && ray->angle <= 3 * PI / 2)
		*x = -TILE_SIZE;
	ray->v_y = game->player.pos_y + (game->player.pos_x - ray->v_x)
		* tan(ray->angle);
	*y = TILE_SIZE * tan(ray->angle);
	if (cos(ray->angle) >= 0)
		*y = -(*y);
	return (ray);
}

void	vertical_intersection(t_mlx *game, t_ray *ray)
{
	double	x;
	double	y;

	ray = help_vertical(game, ray, &x, &y);
	if (ray->v_x < 0 || ray->v_x >= game->width || ray->v_y < 0
		|| ray->v_y >= game->height)
		return ;
	while (1)
	{
		if (ray->v_x <= 0 || ray->v_x >= game->width || ray->v_y <= 0
			|| ray->v_y >= game->height)
			break ;
		if (game->map[(int)(ray->v_y / TILE_SIZE)] && game->map[(int)(ray->v_y
				/ TILE_SIZE)][(int)(ray->v_x / TILE_SIZE)]
			&& game->map[(int)(ray->v_y / TILE_SIZE)][(int)(ray->v_x
				/ TILE_SIZE)] == '1')
			break ;
		if (game->map[(int)((ray->v_y) / TILE_SIZE)]
			&& game->map[(int)((ray->v_y) / TILE_SIZE)][(int)((ray->v_x - 1)
				/ TILE_SIZE)] && game->map[(int)((ray->v_y)
				/ TILE_SIZE)][(int)((ray->v_x - 1) / TILE_SIZE)] == '1')
			break ;
		ray->v_x += x;
		ray->v_y += y;
	}
}

t_ray	get_distance(t_mlx *game, t_ray ray)
{
	double	dist_h;
	double	dist_v;

	dist_h = sqrt(pow(game->player.pos_x - ray.h_x, 2) + pow(game->player.pos_y
				- ray.h_y, 2));
	dist_v = sqrt(pow(game->player.pos_x - ray.v_x, 2) + pow(game->player.pos_y
				- ray.v_y, 2));
	ray.dist = dist_v;
	ray.hit_x = ray.v_x;
	ray.hit_y = ray.v_y;
	ray.is_vertical = 1;
	ray.is_horizontal = 0;
	if (dist_h <= dist_v)
	{
		ray.dist = dist_h;
		ray.hit_x = ray.h_x;
		ray.hit_y = ray.h_y;
		ray.is_vertical = 0;
		ray.is_horizontal = 1;
	}
	return (ray);
}
