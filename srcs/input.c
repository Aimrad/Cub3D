/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:46:20 by artheon           #+#    #+#             */
/*   Updated: 2025/03/05 16:04:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	key(t_game *game)
{
	forward_back(game);
	right_left(game);
	rotate_player(game, ROT_SPEED, FALSE);
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
	{
		game->rotate = -1;
		game->mouse = FALSE;
	}
	else if (keycode == ROTATE_RIGHT)
	{
		game->rotate = 1;
		game->mouse = FALSE;
	}
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
	else if (keycode == ROTATE_LEFT && game->rotate < 0)
	{
		game->mouse = TRUE;
		game->rotate = 0;
	}
	else if (keycode == ROTATE_RIGHT && game->rotate > 0)
	{
		game->mouse = TRUE;
		game->rotate = 0;
	}
	return (0);
}

static void	wrap_mouse_position(t_game *game, int x, int y)
{
	if (x > game->win_width - 20)
	{
		x = 20;
		mlx_mouse_move(game->mlx, game->win, x, y);
	}
	if (x < 20)
	{
		x = game->win_width - 20;
		mlx_mouse_move(game->mlx, game->win, x, y);
	}
}

int	mouse_motion_handler(int x, int y, t_game *game)
{
	static int	old_x = SCREEN_WIDTH / 2;

	wrap_mouse_position(game, x, y);
	if (x == old_x && game->mouse == TRUE)
	{
		game->rotate = 0;
		return (0);
	}
	else if (x < old_x && game->mouse == TRUE)
	{
		game->rotate = 1;
		rotate_player(game, -1, TRUE);
	}
	else if (x > old_x && game->mouse == TRUE)
	{
		game->rotate = 1;
		rotate_player(game, 1, TRUE);
	}
	old_x = x;
	return (0);
}
