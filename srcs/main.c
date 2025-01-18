/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:42:26 by artheon           #+#    #+#             */
/*   Updated: 2025/01/18 01:22:51 by artheon          ###   ########.fr       */
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

char	*read_file(const char *filename)
{
	int		fd;
	char	*temp;
	int		len;
	char	*buffer;
	char	*content;
	ssize_t	bytes;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error\nImpossible d'ouvrir le fichier\n", 1);
	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4))
		error_exit("Error\nLe fichier doit être un .cub\n", 1);
	content = NULL;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		close(fd);
		error_exit("Error\nImpossible d'allouer la mémoire\n", 1);
	}
	bytes = 1;
	while (bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			free(content);
			error_exit("Error\nImpossible de lire le fichier\n", 1);
		}
		buffer[bytes] = '\0';
		temp = content;
		content = ft_strjoin(content, buffer);
		free(temp);
	}
	close(fd);
	if (!content)
		error_exit("Error\nFichier vide\n", 1);
	free(buffer);
	return (content);
}

int	checking_identifier(char *line)
{
	int		i;

	i = 0;
	if (line[i] != 'N' && line[i] != 'S' && line[i] != 'W' && line[i] != 'E' && line[i] != 'F' && line[i] != 'C')
		return (error_exit("Error\nL'identifiant est introuvable\n", 0), 1);
	else if (line[i] == 'N' && line[i + 1] != 'O')
		return (error_exit("Error\nL'identifiant n'est pas correct NO\n", 0), 1);
	else if (line[i] == 'S' && line[i + 1] != 'O')
		return (error_exit("Error\nL'identifiant n'est pas correct SO\n", 0), 1);
	else if (line[i] == 'W' && line[i + 1] != 'E')
		return (error_exit("Error\nL'identifiant n'est pas correct WE\n", 0), 1);
	else if (line[i] == 'E' && line[i + 1] != 'A')
		return (error_exit("Error\nL'identifiant n'est pas correct EA\n", 0), 1);
	else if (line[i] == 'F' && line[i + 1] != ' ')
		return (error_exit("Error\nL'identifiant n'est pas correct F\n", 0), 1);
	else if (line[i] == 'C' && line[i + 1] != ' ')
		return (error_exit("Error\nL'identifiant n'est pas correct C\n", 0), 1);
	i = 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	// double keys
	if (ft_strstr(line + i, "NO"))
		return (error_exit("Error\nDouble identifiant trouvé NO\n", 0), 1);
	else if (ft_strstr(line + i, "SO"))
		return (error_exit("Error\nDouble identifiant trouvé SO\n", 0), 1);
	else if (ft_strstr(line + i, "WE"))
		return (error_exit("Error\nDouble identifiant trouvé WE\n", 0), 1);
	else if (ft_strstr(line + i, "EA"))
		return (error_exit("Error\nDouble identifiant trouvé WE\n", 0), 1);
	else if (ft_strstr(line + i, "F"))
		return (error_exit("Error\nDouble identifiant trouvé F\n", 0), 1);
	else if (ft_strstr(line + i, "C"))
		return (error_exit("Error\nDouble identifiant trouvé C\n", 0), 1);
	return (0);
}

int	checking_identifier_args(char *line, int *count)
{
	int		i;
	int		count_num;
	int		count_comma;
	char	*RGB;
	int		j;

	i = 0;
	count_num = 0;
	count_comma = 0;
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		i += 2;
		++(*count);
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i] || open(line + i, O_RDONLY) < 0)
			return (error_exit("Error\nNO path : invalide\n", 0), 1);
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		i += 2;
		++(*count);
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i] || open(line + i, O_RDONLY) < 0)
			return (error_exit("Error\nSO path : invalide\n", 0), 1);
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		i += 2;
		++(*count);
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i] || open(line + i, O_RDONLY) < 0)
			return (error_exit("Error\nWE path : invalide\n", 0), 1);
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		i += 2;
		++(*count);
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i] || open(line + i, O_RDONLY) < 0)
			return (error_exit("Error\nEA path : invalide\n", 0), 1);
	}
	if (line[i] == 'F')
	{
		i += 1;
		++(*count);
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i])
			return (error_exit("Error\nL'identifiant F n'a pas d'arguments\n", 0), 1);
		while (line[i])
		{
			j = 0;
			while (line[i] && line[i] != ',')
			{
				if (line[i] < '0' || line[i] > '9')
					return (error_exit("Error\nF args ne doit contenir que des chiffres et virgules\n", 0), 1);
				j++;
				i++;
			}
			RGB = ft_substr(line, i - j, j);
			if (ft_atoi(RGB) < 0 || ft_atoi(RGB) > 255)
				return (error_exit("Error\nF args doit être compris entre 0 et 255\n", 0), free(RGB),1);
			else
				count_num++;
			free(RGB);
			if (line[i] == ',')
			{
				count_comma++;
				i++;
			}
		}
		if (count_num < 3 || count_num > 3 || count_comma > 2 || count_comma < 2)
			return (error_exit("Error\nL'identifiant F n'a pas d'arguments valide\n", 0), 1);
	}
	else if (line[i] == 'C')
	{
		i += 1;
		++(*count);
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i])
			return (error_exit("Error\nL'identifiant C n'a pas d'arguments\n", 0), 1);
		while (line[i])
		{
			j = 0;
			while (line[i] && line[i] != ',')
			{
				if (line[i] < '0' || line[i] > '9')
					return (error_exit("Error\nF args ne doit contenir que des chiffres et virgules\n", 0), 1);
				j++;
				i++;
			}
			RGB = ft_substr(line, i - j, j);
			if (ft_atoi(RGB) < 0 || ft_atoi(RGB) > 255)
				return (error_exit("Error\nF args doit être compris entre 0 et 255\n", 0), free(RGB), 1);
			else
				count_num++;
			free(RGB);
			if (line[i] == ',')
			{
				count_comma++;
				i++;
			}
		}
		if (count_num < 3 || count_num > 3 || count_comma > 2 || count_comma < 2)
			return (error_exit("Error\nL'identifiant F n'a pas d'arguments valide\n", 0), 1);
	}
	return (0);
}

int	checking_map_element(char *line, int *count_elem)
{
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!line[i])
		return (0);
	if (checking_identifier(line) == 1 || checking_identifier_args(line, count_elem) == 1)
		return (1);
	return (0);
}

bool	is_valid_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (false);
		i++;
	}
	return (true);
}

char	*check_error(char *file_content)
{
	char	**lines;
	char	*map_location;
	int		i;
	int		count_element;

	lines = ft_split(file_content, '\n');
	map_location = NULL;
	i = 0;
	count_element = 0;
	while (lines[i])
	{
		if(is_valid_map_line(lines[i]))
		{
			map_location = ft_strdup(lines[i]);	
			if (!map_location)
				return (NULL);
			break ;
		}
		if(checking_map_element(lines[i], &count_element) == 1)
		{
			free_split(lines);
			return (NULL);
		}	
		i++;
	}
	free_split(lines);
	if (count_element != 6)
	{
		if (count_element < 6)
			error_exit("Error\nIl manque quelque chose dans la description\n", 0);	
		else
			error_exit("Error\nUn élément est en trop dans la description\n", 0);
		return (NULL);
	}
	if (!map_location)
		error_exit("Error\nCarte non trouvée dans le fichier.\n", 0);
	return (map_location);
}

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

bool	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

t_map	*parse_map(char *map_section)
{
	char	**lines;
	char	*new_line;
	t_map	*map;
	size_t	nbrdechaines;
	int		i;
	int		y;
	int		x;
	int		len;
	int		start;
	int		player_count;
	int		temp;
	
	lines = NULL;
	map = malloc(sizeof(t_map));
	if (!map)
	{
		error_exit("Allocation mémoire échoué.\n", 0);
		return (NULL);
	}
	ft_memset(map, 0, sizeof(t_map));
	i = 0;
	nbrdechaines = 0;
	player_count = 0;
	while (map_section[i])
	{
		if (!is_valid_map_char(map_section[i]) && map_section[i] != '\n')
		{
			free(map);
			error_exit("Caractère invalide dans la carte.\n", 0);
			return (NULL);
		}
		if (is_player_char(map_section[i]))
			player_count++;
		if (map_section[i] == '\n' || map_section[i + 1] == '\0')
			nbrdechaines++;
		i++;
	}
	if (player_count != 1)
	{
		free(map);
		error_exit("Il doit y avoir exactement un joueur sur la carte.\n", 0);
		return (NULL);
	}
	lines = ft_calloc(nbrdechaines + 1, sizeof(char *));
	if (!lines)
	{
		free(map);
		error_exit("Allocation mémoire échoué\n", 0);
		return (NULL);
	}
	i = 0;
	nbrdechaines = 0;
	start = 0;
	while (map_section[i])
	{
		if (map_section[i] == '\n' || map_section[i + 1] == '\0')
		{
			if (map_section[i] == '\n')
				lines[nbrdechaines] = ft_substr(map_section, start, i - start + 0);
			else
				lines[nbrdechaines] = ft_substr(map_section, start, i - start + 1);
			if (!lines[nbrdechaines])
			{
				free_split(lines);
				free(map);
				error_exit("Allocation mémoire échoué\n", 0);
				return (NULL);
			}
			if (lines[nbrdechaines][0] == '\0')
			{
				free_split(lines);
				free(map);
				error_exit("Ligne vide dans la carte.\n", 0);
				return (NULL);
			}
			nbrdechaines++;
			start = i + 1;
		}
		i++;
	}
	map->grid = lines;
	map->height = (int)nbrdechaines;
	map->width = ft_strlen(lines[0]);
	i = 1;
	while (lines[i])
	{
		temp = ft_strlen(lines[i]);
		if (map->width < temp)
			map->width = temp;
		i++;
	}
	len = 0;
	y = 0;
	x = 0;
	while (y < map->height)
	{
		len = ft_strlen(map->grid[y]);
		if (len < map->width)
		{
			new_line = ft_calloc(map->width + 1, sizeof(char));
			if (!new_line)
			{
				free_split(map->grid);
				free(map);
				error_exit("Allocation mémoire échoué", 0);
				return (NULL);	
			}
			ft_memset(new_line, '1', map->width);
			ft_memcpy(new_line, map->grid[y], len);
			free(map->grid[y]);
			map->grid[y] = new_line;
		}
		else
		{
			x = 0;
			while (map->grid[y][x])
			{
				if (map->grid[y][x] == ' ')
					map->grid[y][x] = '1';
				x++;
			}
		}
		y++;
	}
	y = 0;
	x = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] != '1' && (y == 0 || y == map->height - 1 || x == 0 || x == (int)ft_strlen(map->grid[y]) - 1))
			{
				free_split(map->grid);
				free(map);
				error_exit("La carte doit être fermée par des murs.", 0);
				return (NULL);
			}
			if (is_player_char(map->grid[y][x]))
			{
				map->player_y = y;
				map->player_x = x;
				map->player_dir = map->grid[y][x];
				map->grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	return (map);
}

int main(int argc, char **argv)
{
	char	*file_content;
	char	*map_section;
	t_map	*map;

	if (argc != 2)
		error_exit("Error\nUsage: ./cub3d <fichier .cub>\n", 1);
	file_content = read_file(argv[1]);
	// Localisation de la map
	map_section = ft_strstr(file_content, check_error(file_content));
	if(!map_section)
	{
		free(file_content);
		exit(EXIT_FAILURE);
	}
	map = parse_map(map_section);
	if (!map)
	{
		free(file_content);
		exit(EXIT_FAILURE);
	}
	printf("Carte analysée avec succès ! Dimensions : %dx%d\n", map->width, map->height);
	printf("Joueur positionné en (%d, %d) avec orientation %c.\n", map->player_dir, map->player_y, map->player_dir);
	free(file_content);
	free_split(map->grid);
	free(map);
	return (0);
}
