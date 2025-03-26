/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:41:34 by artheon           #+#    #+#             */
/*   Updated: 2025/03/18 16:53:34 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_map_info	validate_map_section(char *map_section)
{
	t_map_info	info;
	int			i;

	info.num_lines = 0;
	info.player_count = 0;
	i = 0;
	while (map_section[i])
	{
		if (!is_valid_map_char(map_section[i]) && map_section[i] != '\n')
		{
			info.num_lines = 0;
			info.player_count = 0;
			error_exit("Caractère invalide dans la carte.\n", 0);
			return (info);
		}
		if (is_player_char(map_section[i]))
			info.player_count++;
		if (map_section[i] == '\n' || map_section[i + 1] == '\0')
			info.num_lines++;
		i++;
	}
	if (info.player_count != 1)
		error_exit("Il doit y avoir exactement un joueur sur la carte.\n", 0);
	return (info);
}

int	validate_elements(char **lines, int *count_element, t_config *config)
{
	int	i;

	i = 0;
	*count_element = 0;
	while (lines[i])
	{
		if (is_valid_map_line(lines[i]))
			break ;
		if (checking_map_element(lines[i], count_element, config) == 1)
			return (1);
		i++;
	}
	return (0);
}

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

bool	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	is_valid_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (false);
		i++;
	}
	return (true);
}
