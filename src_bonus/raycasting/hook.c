/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 03:02:36 by gloukas           #+#    #+#             */
/*   Updated: 2023/12/02 11:59:34 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

int	key_press(int keycode, t_mlx *game)
{
	if (keycode == 119 || keycode == 65362 || keycode == 13
		|| keycode == 126)
		w_key(game);
	if (keycode == 115 || keycode == 65364 || keycode == 1 || keycode == 125)
		s_key(game);
	if (keycode == 97 || keycode == 0)
		a_key(game);
	if (keycode == 100 || keycode == 2)
		d_key(game);
	if (keycode == 65307 || keycode == 53)
		cross_button(game);
	if (keycode == 65361 || keycode == 65363 || keycode == 123
		|| keycode == 124)
		rotation_keys(game, keycode);
	display_3d(game);
	return (0);
}

int	mouse_move(int x, int y, t_mlx *game)
{
	(void)y;
	if (x > WI / 2)
		rotation_keys(game, 65363);
	if (x < WI / 2)
		rotation_keys(game, 65361);
	display_3d(game);
	return (0);
}

int	cross_button(t_mlx *game)
{
	int	i;

	i = -1;
	printf("Game Exited ...\n");
	printf("**********\n");
	free(game->data->file);
	free_array(game->data->file1);
	free(game->data->north);
	free(game->data->south);
	free(game->data->east);
	free(game->data->west);
	free_array(game->data->m);
	free(game->data);
	while (++i < 4)
		mlx_destroy_image(game->ptr, game->textures[i].img);
	free(game->textures);
	mlx_destroy_image(game->ptr, game->img.img);
	mlx_destroy_window(game->ptr, game->win);
	free(game->ptr);
	free(game);
	exit(0);
}

int	check_colision(t_mlx *game, double new_x, double new_y, int key)
{
	int	x;
	int	y;

	x = (int)(new_x / TILE_SIZE);
	y = (int)(new_y / TILE_SIZE);
	if (game->data->m[y][x] == '1')
		return (1);
	if (key == 1 || key == 2)
	{
		if (game->data->m[y][(int)(game->player.pos_x / TILE_SIZE)] == '1')
			return (1);
	}
	if (key == 3 || key == 4)
	{
		if (game->data->m[(int)(game->player.pos_y / TILE_SIZE)][x] == '1')
			return (1);
	}
	return (0);
}
