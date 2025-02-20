/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:38:33 by artheon           #+#    #+#             */
/*   Updated: 2025/02/20 17:34:46 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	checking_identifier(char *line)
{
	int		i;

	i = 0;
	if (line[i] != 'N' && line[i] != 'S' && line[i] != 'W' && line[i] != 'E'
		&& line[i] != 'F' && line[i] != 'C')
		return (error_exit("Error\nL'identifiant est introuvable\n", 0), 1);
	if ((line[i] == 'N' && line[i + 1] != 'O')
		|| (line[i] == 'S' && line[i + 1] != 'O')
		|| (line[i] == 'W' && line[i + 1] != 'E')
		|| (line[i] == 'E' && line[i + 1] != 'A')
		|| (line[i] == 'F' && line[i + 1] != ' ')
		|| (line[i] == 'C' && line[i + 1] != ' '))
		return (error_exit("Error\nIdentifiant incorrect C\n", 0), 1);
	i = 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strstr(line + i, "NO") || ft_strstr(line + i, "SO")
		|| ft_strstr(line + i, "WE") || ft_strstr(line + i, "WE")
		|| ft_strstr(line + i, "EA") || ft_strstr(line + i, "F")
		|| ft_strstr(line + i, "C"))
		return (error_exit("Error\nDouble identifiant trouvé\n", 0), 1);
	return (0);
}

static int	handle_texture(char *line, int *i, int *count, char **texture)
{
	int	fd;
	
	(*i) += 2;
	++(*count);
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
	fd = open(line + *i, O_RDONLY);
	if (!line[*i] || fd < 0)
		return (error_exit("Error\nPath : invalide\n", 0), 1);
	*texture = ft_strdup(line + *i);
	close(fd);
	return (0);
}

static int	handle_color(char *line, int *i, int *count, int *color)
{
	int		count_num;
	int		count_comma;

	count_num = 0;
	count_comma = 0;
	*i += 1;
	++(*count);
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
	if (!line[*i])
		return (error_exit("Error\nPas d'argument color\n", 0), 1);
	while (line[*i])
	{
		color[count_num] = parse_color(line, i);
		if (color[count_num++] == -1)
			return (1);
		if (line[*i] == ',')
		{
			count_comma++;
			(*i)++;
		}
	}
	if (count_num != 3 || count_comma != 2)
		return (error_exit("Error\nColor: arguments invalide\n", 0), 1);
	return (0);
}

int	checking_identifier_args(char *line, int *count, t_config *config)
{
	int		i;

	i = 0;
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (handle_texture(line, &i, count, &(config)->texture_no));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (handle_texture(line, &i, count, &(config)->texture_so));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (handle_texture(line, &i, count, &(config)->texture_we));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (handle_texture(line, &i, count, &(config)->texture_ea));
	if (line[i] == 'F')
		return (handle_color(line, &i, count, config->floor_color));
	else if (line[i] == 'C')
		return (handle_color(line, &i, count, config->ceiling_color));
	return (0);
}

int	checking_map_element(char *line, int *count_elem, t_config *config)
{
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!line[i])
		return (0);
	if (checking_identifier(line) == 1
		|| checking_identifier_args(line, count_elem, config) == 1)
		return (1);
	return (0);
}
