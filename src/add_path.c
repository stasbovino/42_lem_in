/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:58:54 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/20 16:36:35 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	cpy_path(int **dest, int *src)
{
	int		i;

	i = -1;
	while (src[++i] != 0)
		(*dest)[i] = src[i];
}

int		**re_init_table(int ***old, int rooms)
{
	int **new;
	int	i;
	int	len;

	len = rooms * 2;
	new = (int**)malloc(sizeof(int*) * (len + 1));
	i = -1;
	while (++i < len)
	{
		init_path(&(new[i]), rooms);
		if (i < rooms)
		{
			cpy_path(&(new[i]), (*old)[i]);
			free((*old)[i]);
		}
	}
	new[i] = NULL;
	free(*old);
	return (new);
}

void	add_path(int ***tab, int rooms, int **path)
{
	int		i;

	if (*tab == NULL)
	{
		i = -1;
		*tab = (int**)malloc(sizeof(int*) * (rooms + 1));
		while (++i < rooms)
			init_path(&((*tab)[i]), rooms);
		(*tab)[i] = NULL;
	}
	i = 0;
	while ((*tab)[i] && (*tab)[i][0] != 1)
		i++;
	if ((*tab)[i])
	{
		cpy_path(&((*tab)[i]), *path);
//		free(*path);
	}
	else
	{
		*tab = re_init_table(tab, i);
		add_path(tab, rooms, path);
	}
}
