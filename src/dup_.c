/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:34:43 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/18 22:37:36 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			**tab_dup(int **table, int rooms)
{
	int	**duplicate;
	int	i;
	int	j;

	duplicate = allocate_table(rooms);
	i = -1;
	while (++i < (rooms + 2))
	{
		j = -1;
		while (++j < (rooms + 2))
			duplicate[i][j] = table[i][j];
	}
	return (duplicate);
}

int			*dup_path(int *path, int rooms)
{
	int i;
	int	*place;

	i = -1;
	place = (int*)malloc(sizeof(int) * (rooms + 2));
	while (++i < (rooms + 2))
		place[i] = path[i];
	return (place);
}
