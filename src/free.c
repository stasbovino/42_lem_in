/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:33:26 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/18 02:39:58 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		free_split(char ***split, int words, int ret)
{
	int i;

	i = -1;
	while (++i < words)
		free((*split)[i]);
	free(*split);
	return (ret);
}

void	free_tables(int ***int_table, char ***table, int rooms)
{
	int i;

	i = -1;
	if (int_table)
	{
		while (++i < (rooms + 2))
			free((*int_table)[i]);
		free(*int_table);
		i = -1;
	}
	if (table)
	{
		while (++i < (rooms + 1))
			free((*table)[i]);
		free(*table);
	}
}

void	free_input(char ***input, int size)
{
	int i;

	i = -1;
	while (++i < size)
		free((*input)[i]);
	free(*input);
}

void	free_graph(t_graph **graph)
{
	free_tables(&((*graph)->table), &((*graph)->list), (*graph)->rooms);
	if ((*graph)->path)
		free((*graph)->path);
	if ((*graph)->paths)
		free((*graph)->paths);
	free(*graph);
}
