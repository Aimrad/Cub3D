/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:48:09 by artheon           #+#    #+#             */
/*   Updated: 2025/02/17 16:24:30 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	exit_game(t_game *game)
{
	free_split(game->grid);
	free(game->config->texture_no);
	free(game->config->texture_so);
	free(game->config->texture_we);
	free(game->config->texture_ea);
	free(game->config);
	mlx_destroy_image(game->mlx, game->texture[0].img);
	mlx_destroy_image(game->mlx, game->texture[1].img);
	mlx_destroy_image(game->mlx, game->texture[2].img);
	mlx_destroy_image(game->mlx, game->texture[3].img);
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_image(game->mlx, game->mini_map.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(EXIT_SUCCESS);
}
