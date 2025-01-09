/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artheon <artheon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 03:24:05 by artheon           #+#    #+#             */
/*   Updated: 2024/12/11 16:10:58 by artheon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	copy_expand(t_expand_gnl *ctx, char *line, int status, char **env)
{
	ctx->j = 0;
	ctx->expanded = return_exp(line, &ctx->i, status, env);
	while (ctx->expanded[ctx->j])
		ctx->result[ctx->k++] = ctx->expanded[ctx->j++];
	if (line[ctx->i - 1] == '?')
		free(ctx->expanded);
}

void	copy_char(t_expand_gnl *ctx, char *line)
{
	ctx->result[ctx->k++] = line[ctx->i++];
}

char	*return_exp(char *line, int *i, int status, char **env)
{
	char	*expanded;

	expanded = variable(&line[*i], status, env);
	(*i)++;
	if (line[(*i)] && line[(*i)] == '?')
		(*i)++;
	else
	{
		while (line[(*i)] && (ft_isalnum_lib(line[*i]) || line[*i] == '_'))
			(*i)++;
	}
	return (expanded);
}
