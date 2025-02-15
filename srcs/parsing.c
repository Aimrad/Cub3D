/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:38:33 by artheon           #+#    #+#             */
/*   Updated: 2025/02/15 14:40:24 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

int	checking_identifier_args(char *line, int *count, t_config **config)
{
	int		i;
	int		fd;
	int 	value;
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
		fd = open(line + i, O_RDONLY);
		if (!line[i] || fd < 0)
			return (error_exit("Error\nNO path : invalide\n", 0), 1);
		(*config)->texture_no = ft_strdup(line + i);
		close(fd);
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		i += 2;
		++(*count);
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		fd = open(line + i, O_RDONLY);
		if (!line[i] || fd < 0)
			return (error_exit("Error\nSO path : invalide\n", 0), 1);
		(*config)->texture_so = ft_strdup(line + i);
		close(fd);
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		i += 2;
		++(*count);
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		fd = open(line + i, O_RDONLY);
		if (!line[i] || fd < 0)
			return (error_exit("Error\nWE path : invalide\n", 0), 1);
		(*config)->texture_we = ft_strdup(line + i);
		close(fd);
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		i += 2;
		++(*count);
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		fd = open(line + i, O_RDONLY);
		if (!line[i] || fd < 0)
			return (error_exit("Error\nEA path : invalide\n", 0), 1);
		(*config)->texture_ea = ft_strdup(line + i);
		close(fd);
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
			value = (int)ft_atoi(RGB);
			if (value < 0 || value > 255)
				return (error_exit("Error\nF args doit être compris entre 0 et 255\n", 0), free(RGB),1);
			else
			{
				(*config)->floor_color[count_num] = value;
				count_num++;
			}
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
			value = (int)ft_atoi(RGB);
			if (value < 0 || value > 255)
				return (error_exit("Error\nF args doit être compris entre 0 et 255\n", 0), free(RGB), 1);
			else
			{
				(*config)->ceiling_color[count_num] = value;
				count_num++;
			}
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

int	checking_map_element(char *line, int *count_elem, t_config **config)
{
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!line[i])
		return (0);
	if (checking_identifier(line) == 1 || checking_identifier_args(line, count_elem, config) == 1)
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