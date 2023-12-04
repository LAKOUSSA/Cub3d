/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:53:03 by gloukas           #+#    #+#             */
/*   Updated: 2023/11/29 10:56:33 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_mlx	*game;

	game = NULL;
	game = init_game(game, argc, argv);
	if (!game)
		return (1);
	if (init_textures(game) == -1)
		return (1);
	display_3d(game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->win, 17, 0, cross_button, game);
	mlx_loop(game->ptr);
	return (0);
}
