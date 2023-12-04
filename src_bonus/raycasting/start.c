/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloukas <gloukas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:30:17 by gloukas           #+#    #+#             */
/*   Updated: 2023/11/29 10:55:16 by gloukas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

t_mlx	*init_game(t_mlx *game, int argc, char **argv)
{
	game = NULL;
	game = malloc(sizeof(t_mlx));
	if (!game)
		return (NULL);
	game->data = parsing(argc, argv);
	if (game && !game->data)
	{
		free(game);
		return (NULL);
	}
	game->width = get_max_len(game->data->m) * TILE_SIZE;
	game->height = ft_array_length(game->data->m) * TILE_SIZE;
	game->ptr = mlx_init();
	game->win = mlx_new_window(game->ptr, WI, HE, "CUB3D");
	game->img.img = mlx_new_image(game->ptr, WI, HE);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
	game->map = game->data->m;
	game->player.pos_x = (double)game->data->pop_x * TILE_SIZE + TILE_SIZE / 2
		+ 2.5;
	game->player.pos_y = (double)(game->data->pop_y) * TILE_SIZE + TILE_SIZE / 2
		+ 2.5;
	game->player.fov = get_player_angle(game);
	return (game);
}

void	display_mini_map(t_mlx *game)
{
	render_map(game);
	render_player(game);
	mlx_put_image_to_window(game->ptr, game->win, game->img.img, 0, 0);
}

double	get_player_angle(t_mlx *game)
{
	if (game->data->fov == 'N')
		game->player.fov = PI / 2;
	else if (game->data->fov == 'S')
		game->player.fov = 3 * PI / 2;
	else if (game->data->fov == 'W')
		game->player.fov = PI;
	else if (game->data->fov == 'E')
		game->player.fov = 0;
	return (game->player.fov);
}

void	display_3d(t_mlx *game)
{
	raycasting(game);
	display_mini_map(game);
	mlx_put_image_to_window(game->ptr, game->win, game->img.img, 0, 0);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
