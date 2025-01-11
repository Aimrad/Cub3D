/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:42:26 by artheon           #+#    #+#             */
/*   Updated: 2025/01/11 18:22:48 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	error_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
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
		error_exit("Error\nImpossible d'ouvrir le fichier\n");
	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4))
		error_exit("Error\nLe fichier doit être un .cub\n");
	content = NULL;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		error_exit("Error\nImpossible d'allouer la mémoire\n");
	bytes = 1;
	while (bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			free(content);
			error_exit("Error\nImpossible de lire le fichier\n");
		}
		buffer[bytes] = '\0';
		temp = content;
		content = ft_strjoin(content, buffer);
		free(temp);
	}
	close(fd);
	if (!content)
		error_exit("Error\nFichier vide\n");
	free(buffer);
	return (content);
}

void	checking_identifier(char *line)
{
	int		i;

	i = 0;
	if (line[i] != 'N' || line[i] != 'S' || line[i] != 'W' || line[i] != 'E' || line[i] != 'F' || line[i] != 'C')
		error_exit("Error\nL'identifiant est introuvable\n");
	else if (line[i] == 'N' && line[i + 1] != 'O')
		error_exit("Error\nL'identifiant n'est pas correct NO\n");
	else if (line[i] == 'S' && line[i + 1] != 'O')
		error_exit("Error\nL'identifiant n'est pas correct SO\n");
	else if (line[i] == 'W' && line[i + 1] != 'E')
		error_exit("Error\nL'identifiant n'est pas correct WE\n");
	else if (line[i] == 'E' && line[i + 1] != 'A')
		error_exit("Error\nL'identifiant n'est pas correct EA\n");
	else if (line[i] == 'F' && line[i + 1] != ' ')
		error_exit("Error\nL'identifiant n'est pas correct F\n");
	else if (line[i] == 'C' && line[i + 1] != ' ')
		error_exit("Error\nL'identifiant n'est pas correct C\n");
	i = 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	// double keys
	if (ft_strstr(line + i, "NO"))
		error_exit("Error\nDouble identifiant trouvé NO\n");
	else if (ft_strstr(line + i, "SO"))
		error_exit("Error\nDouble identifiant trouvé SO\n");
	else if (ft_strstr(line + i, "WE"))
		error_exit("Error\nDouble identifiant trouvé WE\n");
	else if (ft_strstr(line + i, "EA"))
		error_exit("Error\nDouble identifiant trouvé WE\n");
	else if (ft_strstr(line + i, "F"))
		error_exit("Error\nDouble identifiant trouvé F\n");
	else if (ft_strstr(line + i, "C"))
		error_exit("Error\nDouble identifiant trouvé C\n");
	return (0);
}

void	checking_identifier_args(char *line)
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
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i] || open(line + i, O_RDONLY) < 0)
			error_exit("Error\nNO path : invalide\n");
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		i += 2;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i] || open(line + i, O_RDONLY) < 0)
			error_exit("Error\nSO path : invalide\n");
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		i += 2;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i] || open(line + i, O_RDONLY) < 0)
			error_exit("Error\nWE path : invalide\n");
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		i += 2;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i] || open(line + i, O_RDONLY) < 0)
			error_exit("Error\nEA path : invalide\n");
	}
	if (line[i] == 'F')
	{
		i += 1;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i])
			error_exit("Error\nL'identifiant F n'a pas d'arguments\n");
		while (line[i])
		{
			j = 0;
			while (line[i] && line[i] != ',')
			{
				if (line[i] < '0' || line[i] > '9')
					error_exit("Error\nF args ne doit contenir que des chiffres et virgules\n");
				j++;
				i++;
			}
			RGB = ft_substr(line, i - j, j);
			if (ft_atoi(RGB) < 0 || ft_atoi(RGB) > 255)
				error_exit("Error\nF args doit être compris entre 0 et 255\n");
			else
				count_num++;
			if (line[i] == ',')
			{
				count_comma++;
				i++;
			}
		}
		if (count_num < 3 || count_num > 3 || count_comma > 2 || count_comma < 2)
			error_exit("Error\nL'identifiant F n'a pas d'arguments valide\n");
	}
	else if (line[i] == 'C')
	{
		i += 1;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i])
			error_exit("Error\nL'identifiant C n'a pas d'arguments\n");
		while (line[i])
		{
			j = 0;
			while (line[i] && line[i] != ',')
			{
				if (line[i] < '0' || line[i] > '9')
					error_exit("Error\nF args ne doit contenir que des chiffres et virgules\n");
				j++;
				i++;
			}
			RGB = ft_substr(line, i - j, j);
			if (ft_atoi(RGB) < 0 || ft_atoi(RGB) > 255)
				error_exit("Error\nF args doit être compris entre 0 et 255\n");
			else
				count_num++;
			if (line[i] == ',')
			{
				count_comma++;
				i++;
			}
		}
		if (count_num < 3 || count_num > 3 || count_comma > 2 || count_comma < 2)
			error_exit("Error\nL'identifiant F n'a pas d'arguments valide\n");
	}
}

void	checking_map_element(char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	checking_identifier(line);
	checking_identifier_args(line);
}

void	check_error(char *file_content)
{
	char	**lines;
	int		i;

	lines = ft_split(file_content, '\n');
	i = 0;
	while (lines[i])
	{
		checking_map_element(lines[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	char	*file_content;
	// char	*map_section;

	if (argc != 2)
		error_exit("Error\nUsage: ./cub3d <fichier .cub>\n");
	file_content = read_file(argv[1]);
	check_error(file_content);
	return (0);
}
