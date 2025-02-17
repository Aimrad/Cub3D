/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:17:52 by artheon           #+#    #+#             */
/*   Updated: 2025/02/17 17:28:53 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	forward_back(t_game *game)
{
	if (game->z == 1)
	{
		if (game->grid[(int)(game->pos_y + game->dir_y * MOVE_SPEED)]
			[(int)game->pos_x] != '1')
			game->pos_y += game->dir_y * MOVE_SPEED;
		if (game->grid[(int)game->pos_y]
			[(int)(game->pos_x + game->dir_x * MOVE_SPEED)] != '1')
			game->pos_x += game->dir_x * MOVE_SPEED;
	}
	if (game->s == 1)
	{
		if (game->grid[(int)(game->pos_y - game->dir_y * MOVE_SPEED)]
			[(int)game->pos_x] != '1')
			game->pos_y -= game->dir_y * MOVE_SPEED;
		if (game->grid[(int)game->pos_y]
			[(int)(game->pos_x - game->dir_x * MOVE_SPEED)] != '1')
			game->pos_x -= game->dir_x * MOVE_SPEED;
	}
}

void	right_left(t_game *game)
{
	double	strafe_x;
	double	strafe_y;

	if (game->d == 1)
	{
		strafe_x = -game->dir_y;
		strafe_y = game->dir_x;
		if (game->grid[(int)(game->pos_y + strafe_y * MOVE_SPEED)]
			[(int)game->pos_x] != '1')
			game->pos_y += strafe_y * MOVE_SPEED;
		if (game->grid[(int)game->pos_y]
			[(int)(game->pos_x + strafe_x * MOVE_SPEED)] != '1')
			game->pos_x += strafe_x * MOVE_SPEED;
	}
	if (game->q == 1)
	{
		strafe_x = game->dir_y;
		strafe_y = -game->dir_x;
		if (game->grid[(int)(game->pos_y + strafe_y * MOVE_SPEED)]
			[(int)game->pos_x] != '1')
			game->pos_y += strafe_y * MOVE_SPEED;
		if (game->grid[(int)game->pos_y]
			[(int)(game->pos_x + strafe_x * MOVE_SPEED)] != '1')
			game->pos_x += game->dir_x * MOVE_SPEED;
	}
}

void    rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (game->rotate_left == 1)
	{
		old_dir_x = game->dir_x;
		game->dir_x = game->dir_x * cos(-ROT_SPEED) - game->dir_y \
		* sin(-ROT_SPEED);
		game->dir_y = old_dir_x * sin(-ROT_SPEED) + game->dir_y \
		* cos(-ROT_SPEED);
		old_plane_x = game->plane_x;
		game->plane_x = game->plane_x * cos(-ROT_SPEED) - game->plane_y \
		* sin(-ROT_SPEED);
		game->plane_y = old_plane_x * sin(-ROT_SPEED) + game->plane_y \
		* cos(-ROT_SPEED);
	}
}

void    rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (game->rotate_right == 1)
	{
		old_dir_x = game->dir_x;
		game->dir_x = game->dir_x * cos(ROT_SPEED) - game->dir_y \
		* sin(ROT_SPEED);
		game->dir_y = old_dir_x * sin(ROT_SPEED) + game->dir_y * cos(ROT_SPEED);
		old_plane_x = game->plane_x;
		game->plane_x = game->plane_x * cos(ROT_SPEED) - game->plane_y \
		* sin(ROT_SPEED);
		game->plane_y = old_plane_x * sin(ROT_SPEED) + game->plane_y \
		* cos(ROT_SPEED);
	}
}