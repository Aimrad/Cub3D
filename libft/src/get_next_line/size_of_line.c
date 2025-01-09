/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_of_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 03:02:57 by artheon           #+#    #+#             */
/*   Updated: 2024/12/11 14:56:47 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*name(char *line)
{
	int		i;
	int		var_index;
	char	*var_name;

	i = 1;
	var_index = 0;
	while (line[i] && line[i] != '$'
		&& (ft_isalnum_lib(line[i]) || line[i] == '_'))
		i++;
	var_name = malloc(i * sizeof(char));
	if (!var_name)
		return (NULL);
	i = 1;
	while (line[i] && line[i] != '$'
		&& (ft_isalnum_lib(line[i]) || line[i] == '_'))
		var_name[var_index++] = line[i++];
	var_name[var_index] = '\0';
	return (var_name);
}

static char	*value(char *line, int status, char **env)
{
	char	*var_name;
	char	*var_value;
	int		k;
	int		j;

	k = 0;
	var_value = NULL;
	if (line[1] == '?')
		return (ft_itoa_lib(status));
	var_name = name(line);
	if (!var_name)
		return (NULL);
	j = ft_strlen_lib(var_name);
	while (env[k])
	{
		if (ft_strncmp_lib(env[k], var_name, j) == 0 && env[k][j] == '=')
		{
			var_value = &env[k][j + 1];
			break ;
		}
		k++;
	}
	free(var_name);
	return (var_value);
}

char	*variable(char *line, int status, char **env)
{
	char	*var_value;

	var_value = value(line, status, env);
	if (var_value)
		return (var_value);
	return ("\0");
}

size_t	expansion(char *line, int *i, int status, char **env)
{
	char	*var_value;
	size_t	var_size;

	var_size = 0;
	var_value = variable(&line[*i], status, env);
	if (var_value)
	{
		var_size = ft_strlen_lib(var_value);
		if (line[(*i) + 1] == '?' || ft_isdigit_lib(line[(*i) + 1]))
			free(var_value);
	}
	(*i)++;
	if (line[(*i)] && line[(*i)] == '?')
		(*i)++;
	else
	{
		while (line[(*i)] && line[(*i)] != '$'
			&& (ft_isalnum_lib(line[*i]) || line[*i] == '_'))
			(*i)++;
	}
	return (var_size);
}

size_t	regular(char *line, int *i, int status, char **env)
{
	size_t	size;

	size = 0;
	while (line[*i])
	{
		if (line[*i] == '$')
			size += expansion(line, i, status, env);
		else
		{
			size++;
			(*i)++;
		}
	}
	return (size);
}
