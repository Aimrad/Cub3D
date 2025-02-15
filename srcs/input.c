/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:46:20 by artheon           #+#    #+#             */
/*   Updated: 2025/02/15 14:47:17 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	key(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	strafe_x;
	double	strafe_y;
	double	move_speed;
	double	rot_speed;

	move_speed = 0.1;
	rot_speed = 0.05;
	if (game->z == 1)
	{
		if (game->grid[(int)(game->pos_y + game->dir_y * move_speed)][(int)game->pos_x] != '1')
			game->pos_y += game->dir_y * move_speed; 
		if (game->grid[(int)game->pos_y][(int)(game->pos_x + game->dir_x * move_speed)] != '1')
			game->pos_x += game->dir_x * move_speed;
	}
	if (game->s == 1)
	{
		if (game->grid[(int)(game->pos_y - game->dir_y * move_speed)][(int)game->pos_x] != '1')
			game->pos_y -= game->dir_y * move_speed; 
		if (game->grid[(int)game->pos_y][(int)(game->pos_x - game->dir_x * move_speed)] != '1')
			game->pos_x -= game->dir_x * move_speed;
	}
	if (game->d == 1)
	{
		strafe_x = -game->dir_y;
		strafe_y = game->dir_x;
		if (game->grid[(int)(game->pos_y + strafe_y * move_speed)][(int)game->pos_x] != '1')
			game->pos_y += strafe_y * move_speed; 
		if (game->grid[(int)game->pos_y][(int)(game->pos_x + strafe_x * move_speed)] != '1')
			game->pos_x += strafe_x * move_speed;
	}
	if (game->q == 1)
	{
		strafe_x = game->dir_y;
		strafe_y = -game->dir_x;
		if (game->grid[(int)(game->pos_y + strafe_y * move_speed)][(int)game->pos_x] != '1')
			game->pos_y += strafe_y * move_speed; 
		if (game->grid[(int)game->pos_y][(int)(game->pos_x + strafe_x * move_speed)] != '1')
			game->pos_x += game->dir_x * move_speed;
	}
	if (game->rotate_left == 1)
	{
		old_dir_x = game->dir_x;
		game->dir_x = game->dir_x * cos(-rot_speed) - game->dir_y * sin(-rot_speed);
		game->dir_y = old_dir_x * sin(-rot_speed) + game->dir_y * cos(-rot_speed);
		old_plane_x = game->plane_x;
		game->plane_x = game->plane_x * cos(-rot_speed) - game->plane_y * sin(-rot_speed);
		game->plane_y = old_plane_x * sin(-rot_speed) + game->plane_y * cos(-rot_speed);
	}
	if (game->rotate_right == 1)
	{
		old_dir_x = game->dir_x;
		game->dir_x = game->dir_x * cos(rot_speed) - game->dir_y * sin(rot_speed);
		game->dir_y = old_dir_x * sin(rot_speed) + game->dir_y * cos(rot_speed);
		old_plane_x = game->plane_x;
		game->plane_x = game->plane_x * cos(rot_speed) - game->plane_y * sin(rot_speed);
		game->plane_y = old_plane_x * sin(rot_speed) + game->plane_y * cos(rot_speed);
	}
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