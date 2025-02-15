/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:36:29 by artheon           #+#    #+#             */
/*   Updated: 2025/02/15 14:37:46 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_char(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		printf("char : %s\n", split[i]);
		i++;
	}
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	error_exit(char *msg, int flags)
{
	ft_putstr_fd(msg, 2);
	if (flags)
		exit(EXIT_FAILURE);	
}

int create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}