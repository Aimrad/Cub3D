/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:50:03 by artheon           #+#    #+#             */
/*   Updated: 2025/01/13 20:47:03 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_3D_H
# define CUBE_3D_H

# include <stdbool.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"

typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    int     player_x;
    int     player_y;
    char    player_dir;
}   t_map;

void	error_exit(char *msg, int flags);

#endif