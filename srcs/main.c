/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:42:26 by artheon           #+#    #+#             */
/*   Updated: 2025/02/28 16:51:27 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static char	*read_join_file(int fd)
{
	char	*content;
	char	*new_content;
	char	*temp;

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
	get_next_line(fd, 1);
	return (content);
}

char	*read_file(const char *filename)
{
	int		fd;
	char	*content;
	int		len;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error\nImpossible d'ouvrir le fichier\n", 1);
	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4))
		error_exit("Error\nLe fichier doit être un .cub\n", 1);
	content = read_join_file(fd);
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
	mlx_mouse_move(game->mlx, game->win, game->win_width / 2,
		game->win_height / 2);
	mlx_hook(game->win, MotionNotify, PointerMotionMask, mouse_motion_handler, game);
}

static char	*get_map_section(char *file_content, t_config *config)
{
	char	*temp;
	char	*map_section;

	temp = check_error(file_content, config);
	map_section = ft_strstr(file_content, temp);
	if (!map_section)
	{
		free(file_content);
		exit(EXIT_FAILURE);
	}
	free(temp);
	return (map_section);
}

static char	*get_map_section(char *file_content, t_config *config)
{
	char	*temp;
	char	*map_section;

	temp = check_error(file_content, config);
	map_section = ft_strstr(file_content, temp);
	if (!map_section)
	{
		free(file_content);
		exit(EXIT_FAILURE);
	}
	free(temp);
	return (map_section);
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
	ft_memset(&config, 0, sizeof(t_config));
	map_section = get_map_section(file_content, &config);
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
