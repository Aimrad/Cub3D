/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:42:26 by artheon           #+#    #+#             */
/*   Updated: 2025/01/13 23:38:13 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

int	is_only_digits(char *lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		while (lines[i] == ' ' || lines[i] == '\t')
			i++;
		if (lines[i] < '0' || lines[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_error(char *file_content)
{
	char	**lines;
	int		i;
	int		count_element;

	lines = ft_split(file_content, '\n');
	i = 0;
	count_element = 0;
	while (lines[i])
	{
		if(is_only_digits(lines[i]))
			break ;
		if(checking_map_element(lines[i], &count_element) == 1)
		{
			free_split(lines);
			return (1);
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
		return (1);
	}
	return (0);
}

char	*locate_map_section(char *file_content)
{
	char	**lines;
	char	*map_section;
	char	*temp;
	int		i;
	int		start_index;

	lines = ft_split(file_content, "\n");
	i = 0;
	start_index = -1;
	while (lines[i])
	{
		if (is_only_digits(lines[i]))
		{
			start_index = i;
			break ;
		}
		i++;
	}
	if (start_index == -1)
	{
		free_split(lines);
		return (NULL);
	}
	map_section = ft_strdup(lines[start_index]);
	i = start_index + 1;
	while (lines[i])
	{
		temp = map_section;
		map_section = ft_strjoin(map_section, "\n");
		free(temp);
		temp = map_section;
		map_section = ft_strjoin(map_section, lines[i]);
		free(temp);
		i++;
	}
	free_split(lines);
	return (map_section);
}

int main(int argc, char **argv)
{
	char	*file_content;
	char	*map_section;

	if (argc != 2)
		error_exit("Error\nUsage: ./cub3d <fichier .cub>\n", 1);
	file_content = read_file(argv[1]);
	if(check_error(file_content) == 1)
	{
		free(file_content);
		exit(EXIT_FAILURE);
	}
	// Localisation de la map
	map_section = locate_map_section(file_content);
	if (!map_section)
	{
		free(file_content);
		error_exit("Error\nImpossible de localiser la section de la carte\n", 1);
	}
	free(map_section);
	free(file_content);
	return (0);
}
