/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:17:52 by artheon           #+#    #+#             */
/*   Updated: 2025/03/05 16:03:42 by marvin           ###   ########.fr       */
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
			game->pos_x += strafe_x * MOVE_SPEED;
	}
}

static void	rotate_left_right(t_game *game, double rotspeed)
{
	double		tmp_x;

	if (game->rotate != 0)
	{
		tmp_x = game->dir_x;
		game->dir_x = game->dir_x * cos(rotspeed) - game->dir_y * sin(rotspeed);
		game->dir_y = tmp_x * sin(rotspeed) + game->dir_y * cos(rotspeed);
		tmp_x = game->plane_x;
		game->plane_x = game->plane_x * cos(rotspeed) - game->plane_y \
		* sin(rotspeed);
		game->plane_y = tmp_x * sin(rotspeed) + game->plane_y * cos(rotspeed);
	}
}

void	rotate_player(t_game *game, double rotdir, int mouse)
{
	double	rotspeed;

	if (game->rotate < 0)
		rotspeed = -ROT_SPEED * rotdir;
	else
		rotspeed = ROT_SPEED * rotdir;
	if (mouse)
		rotspeed *= MOUSE_BALANCE;
	rotate_left_right(game, rotspeed);
}
