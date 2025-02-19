/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:42:26 by artheon           #+#    #+#             */
/*   Updated: 2025/02/19 18:29:20 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*read_file(const char *filename)
{
	int		fd;
	char	*temp;
	int		len;
	char	*content;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error\nImpossible d'ouvrir le fichier\n", 1);
	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4))
		error_exit("Error\nLe fichier doit être un .cub\n", 1);
	content = NULL;
	temp = get_next_line(fd, 0);
	while (temp)
	{
		content = ft_strjoin(content, temp);
		free(temp);
		temp = get_next_line(fd, 0);
	}
	close(fd);
	get_next_line(fd, 1);
	if (!content)
		error_exit("Error\nFichier vide\n", 1);
	return (content);
}

int	main(int argc, char **argv)
{
	char		*file_content;
	char		*map_section;
	t_game		*map;
	t_config	*config;

	if (argc != 2)
		error_exit("Error\nUsage: ./cub3d <fichier .cub>\n", 1);
	file_content = read_file(argv[1]);
	config = malloc(sizeof(t_config));
	if (!config)
	{
		free(file_content);
		exit(EXIT_FAILURE);
	}
	ft_memset(config, 0, sizeof(t_config));
	map_section = ft_strstr(file_content, check_error(file_content, &config));
	if (!map_section)
	{
		free(file_content);
		exit(EXIT_FAILURE);
	}
	map = parse_map(map_section, config);
	if (!map)
	{
		free(file_content);
		exit(EXIT_FAILURE);
	}
	free(file_content);
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	load_all_texture(map);
	init_image(map);
	mlx_hook(map->win, 17, 1L << 17, exit_game, map);
	mlx_hook(map->win, 2, 1L << 0, key_press, map);
	mlx_loop_hook(map->mlx, render, map);
	mlx_hook(map->win, 3, 1L << 1, key_release, map);
	mlx_loop(map->mlx);
	return (0);
}
