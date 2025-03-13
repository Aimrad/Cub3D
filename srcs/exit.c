/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:48:09 by artheon           #+#    #+#             */
/*   Updated: 2025/02/28 16:47:28 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	free_texture(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < game->texture[i].frame_count)
		{
			mlx_destroy_image(game->mlx, game->texture[i].img[j]);
			j++;
		}
		free(game->texture[i].img);
		free(game->texture[i].data);
		i++;
	}
}

void	free_checker(t_config *config)
{
	if (config->texture_no)
	{
		free_split(config->texture_no);
		config->texture_no = NULL;
	}
	if (config->texture_so)
	{
		free_split(config->texture_so);
		config->texture_so = NULL;
	}
	if (config->texture_we)
	{
		free_split(config->texture_we);
		config->texture_we = NULL;
	}
	if (config->texture_ea)
	{
		free_split(config->texture_ea);
		config->texture_ea = NULL;
	}
}

int	exit_game(t_game *game)
{
	free_split(game->grid);
	free_split(game->config.texture_no);
	free_split(game->config.texture_so);
	free_split(game->config.texture_we);
	free_split(game->config.texture_ea);
	free_texture(game);
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_image(game->mlx, game->mini_map.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(EXIT_SUCCESS);
}
