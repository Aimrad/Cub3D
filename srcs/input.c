/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:46:20 by artheon           #+#    #+#             */
/*   Updated: 2025/02/17 17:30:57 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	key(t_game *game)
{
	forward_back(game);
	right_left(game);
	rotate_left(game);
	rotate_right(game);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		exit_game(game);
	if (keycode == Z)
		game->z = 1;
	else if (keycode == S)
		game->s = 1;
	else if (keycode == D)
		game->d = 1;
	else if (keycode == Q)
		game->q = 1;
	else if (keycode == ROTATE_LEFT)
		game->rotate_left = 1;
	else if (keycode == ROTATE_RIGHT)
		game->rotate_right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == Z)
		game->z = 0;
	else if (keycode == S)
		game->s = 0;
	else if (keycode == D)
		game->d = 0;
	else if (keycode == Q)
		game->q = 0;
	else if (keycode == ROTATE_LEFT)
		game->rotate_left = 0;
	else if (keycode == ROTATE_RIGHT)
		game->rotate_right = 0;
	return (0);
}
