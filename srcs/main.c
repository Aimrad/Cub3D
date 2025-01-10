/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:42:26 by artheon           #+#    #+#             */
/*   Updated: 2025/01/10 17:10:11 by artheon          ###   ########.fr       */
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

int		check_syntax(char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
	{
		j = i;
		while (line[j + 1] != ' ')
			j++;
		if (j > 2)
			return (0);
		if (line[j] == line[j - 1])
			return (0);
		i = j;
		if (line[i + 1] != '.')
			return (0);
	}
	return (1);
}

void	ft_find_map(char *file_content)
{
	int		i;
	char	*check;

	i = 0;
	while (file_content[i] != '\0' && i <= 1)
	{
		while (file_content[i] != '\n')
			i++;
		check = ft_substr(file_content, 0, i);
		if (check_syntax(check) == 0)
			error_exit("Error\nSyntaxe de la map incorrecte\n");
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
	ft_find_map(file_content);
	return (0);
}
