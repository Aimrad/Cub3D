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

int main(int argc, char **argv)
{
	char	*file_content;
	char	*map_section;
	t_game	*map;
	t_config *config;
	// Le parsing
	if (argc != 2)
		error_exit("Error\nUsage: ./cub3d <fichier .cub>\n", 1);
	file_content = read_file(argv[1]);
		// Localisation de la map
	config = malloc(sizeof(t_config));
	if(!config)
	{
		free(file_content);
		exit(EXIT_FAILURE);
	}
	ft_memset(config, 0, sizeof(t_config));
	map_section = ft_strstr(file_content, check_error(file_content, &config));
	if(!map_section)
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
	// printf("Textures chargées :\n");
    // printf("NO : %s\nSO : %s\nWE : %s\nEA : %s\n", map->config->texture_no, map->config->texture_so, map->config->texture_we, map->config->texture_ea);
    // printf("Couleurs chargées :\n");
    // printf("Sol : %d,%d,%d\nPlafond : %d,%d,%d\n",
    //        map->config->floor_color[0], map->config->floor_color[1], map->config->floor_color[2],
    //        map->config->ceiling_color[0], map->config->ceiling_color[1], map->config->ceiling_color[2]);
	// printf("Carte analysée avec succès ! Dimensions : %dx%d\n", map->width, map->height);
	// printf("Joueur positionné en (%f, %f) avec orientation (%f, %f).\n", map->pos_x, map->pos_y, map->dir_x, map->dir_y);
	// La Minilibx
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
