/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:48:05 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/10 17:59:26 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		reweight(int **table, int *path)
{
	int	end;
	int	i;

	i = 2;
	end = path[path[0]];
	while (path[i + 1] != end)
	{
		table[path[i]][path[i + 1]] -= 1;
		table[path[i + 1]][path[i]] += 1;
		i++;
	}
}

void		restruct_table(int **table, int **begin, int rooms)
{
	int i;
	int j;

	i = 1;
	while (++i < rooms)
	{
		j = 0;
		while (++j < rooms)
		{
			if (begin[i][j] == 1 && table[i][j] != 0)
				begin[i][j] = 0;
		}
	}
}

int			restore_table(int **begin, int rooms, int opt)
{
	static int	**fixed = NULL;
	int			i;
	int			j;

	if (opt == 1)
	{
		if (fixed)
			free_tables(&fixed, NULL, rooms);
		return (0);
	}
	if (fixed == NULL)
	{
		fixed = tab_dup(begin, rooms);
		if (!fixed)
			return (1);
		return (0);
	}
	i = 0;
	while (++i < (rooms + 2))
	{
		j = 0;
		while (++j < (rooms + 2))
			begin[i][j] = fixed[i][j];
	}
	return (0);
}

int			back_weight(int **table, int *path)
{
	int	end;
	int	i;

	i = 2;
	end = path[path[0]];
	while (path[i + 1] != end)
	{
		table[path[i]][path[i + 1]] += 1;
		table[path[i + 1]][path[i]] -= 1;
		i++;
	}
	return (1);
}
