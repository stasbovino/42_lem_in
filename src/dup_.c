/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:34:43 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/05 22:06:57 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			**tab_dup(int **table, int rooms)
{
	int	**duplicate;
	int	i;
	int	j;

	if (!(duplicate = allocate_table(rooms)))
		return (NULL);
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
	if (!(place = (int*)malloc(sizeof(int) * (rooms + 2))))
		return (NULL);
	while (++i < (rooms + 2))
		place[i] = path[i];
	return (place);
}
