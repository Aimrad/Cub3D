/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:41:10 by artheon           #+#    #+#             */
/*   Updated: 2025/02/20 18:36:25 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static char	*find_map_location(char **lines)
{
	int		i;
	char	*map_location;

	map_location = NULL;
	i = 0;
	while (lines[i])
	{
		if (is_valid_map_line(lines[i]))
		{
			map_location = ft_strdup(lines[i]);
			if (!map_location)
				return (NULL);
			break ;
		}
		i++;
	}
	return (map_location);
}

char	*check_error(char *file_content, t_config *config)
{
	char	**lines;
	char	*map_location;
	int		count_element;

	lines = ft_split(file_content, '\n');
	if (!lines)
		return (NULL);
	if (validate_elements(lines, &count_element, config))
	{
		free_split(lines);
		return (NULL);
	}
	map_location = find_map_location(lines);
	free_split(lines);
	if (count_element != 6)
	{
		if (count_element < 6)
			error_exit("Error\nIl manque des elements dans le .cub\n", 0);
		else
			error_exit("Error\nUn élément est en trop dans le .cub\n", 0);
		return (NULL);
	}
	if (!map_location)
		error_exit("Error\nCarte non trouvée dans le fichier.\n", 0);
	return (map_location);
}

static int	handle_line(t_map_info *context, int end)
{
	if (context->map_section[end] == '\n')
		context->lines[context->nbrdechaines] = ft_substr(context->map_section, \
			context->start, end - context->start);
	else
		context->lines[context->nbrdechaines] = ft_substr(context->map_section, \
			context->start, end - context->start + 1);
	if (!context->lines[context->nbrdechaines])
	{
		free_split(context->lines);
		return (0);
	}
	if (context->lines[context->nbrdechaines][0] == '\0')
	{
		free_split(context->lines);
		error_exit("Ligne vide dans la carte\n", 0);
		return (0);
	}
	(context->nbrdechaines)++;
	return (1);
}

static char	**split_map_lines(char *map_section, int num_lines)
{
	t_map_info	context;
	int			i;

	context.lines = ft_calloc(num_lines + 1, sizeof(char *));
	if (!context.lines)
		return (NULL);
	i = 0;
	context.map_section = map_section;
	context.nbrdechaines = 0;
	context.start = 0;
	while (map_section[i])
	{
		if (map_section[i] == '\n' || map_section[i + 1] == '\0')
		{
			if (!handle_line(&context, i))
				return (NULL);
			context.start = i + 1;
		}
		i++;
	}
	return (context.lines);
}

t_game	*parse_map(char *map_section, t_config config)
{
	t_map_info	info;
	t_game		*map;

	map = malloc(sizeof(t_game));
	if (!map)
	{
		error_exit("Allocation mémoire échoué.\n", 0);
		return (NULL);
	}
	ft_memset(map, 0, sizeof(t_game));
	map->config = config;
	info = validate_map_section(map_section);
	if (info.num_lines == 0 || info.num_lines == 0)
		return (free(map), NULL);
	map->height = info.num_lines;
	map->grid = split_map_lines(map_section, info.num_lines);
	if (!map->grid)
		return (error_exit("Allocation mémoire échoué\n", 0), free(map), NULL);
	pad_map_lines(map);
	init_player_and_check_walls(map);
	return (map);
}
