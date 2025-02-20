/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:42:26 by artheon           #+#    #+#             */
/*   Updated: 2025/02/20 19:09:04 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*read_file(const char *filename)
{
	int		fd;
	char	*temp;
	int		len;
	char	*content;
	char	*new_content;

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
		new_content = ft_strjoin(content, temp);
		free(content);
		free(temp);
		content = new_content;
		temp = get_next_line(fd, 0);
	}
	close(fd);
	get_next_line(fd, 1);
	if (!content)
		error_exit("Error\nFichier vide\n", 1);
	return (content);
}

void	initialize_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	load_all_texture(game);
	init_image(game);
	mlx_hook(game->win, 17, 1L << 17, exit_game, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
}

int	main(int argc, char **argv)
{
	char		*file_content;
	char		*map_section;
	t_game		*map;
	t_config	config;

	if (argc != 2)
		error_exit("Error\nUsage: ./cub3d <fichier .cub>\n", 1);
	file_content = read_file(argv[1]);
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
	initialize_game(map);
	mlx_loop(map->mlx);
	return (0);
}
