/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:04:17 by gloukas           #+#    #+#             */
/*   Updated: 2023/11/29 15:48:49 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	w_key(t_mlx *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + MOVE_SPEED * cos(game->player.fov);
	new_y = game->player.pos_y - MOVE_SPEED * sin(game->player.fov);
	if (!check_colision(game, new_x, new_y, 1))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

void	s_key(t_mlx *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - MOVE_SPEED * cos(game->player.fov);
	new_y = game->player.pos_y + MOVE_SPEED * sin(game->player.fov);
	if (!check_colision(game, new_x, new_y, 2))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

void	a_key(t_mlx *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + MOVE_SPEED * cos(game->player.fov + PI / 2);
	new_y = game->player.pos_y - MOVE_SPEED * sin(game->player.fov + PI / 2);
	if (!check_colision(game, new_x, new_y, 3))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

void	d_key(t_mlx *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - MOVE_SPEED * cos(game->player.fov + PI / 2);
	new_y = game->player.pos_y + MOVE_SPEED * sin(game->player.fov + PI / 2);
	if (!check_colision(game, new_x, new_y, 4))
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
}

void	rotation_keys(t_mlx *game, int keycode)
{
	if (keycode == 65361 || keycode == 123)
		game->player.fov += 0.1;
	else if (keycode == 65363 || keycode == 124)
		game->player.fov -= 0.1;
}
