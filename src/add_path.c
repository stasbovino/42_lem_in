/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:58:54 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/23 12:41:21 by sts              ###   ########.fr       */
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

int		**re_init_table(int ***old, int rooms, int bytes)
{
	int **new;
	int	i;
	int	len;

	len = bytes * 2;
	new = (int**)malloc(sizeof(int*) * (len + 1));
	i = -1;
	while (++i < len)
	{
		init_path(&(new[i]), rooms);
		if (i < bytes)
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
	int		bytes;

	bytes = 10;
	if (*tab == NULL)
	{
		i = -1;
		*tab = (int**)malloc(sizeof(int*) * (bytes + 1));
		while (++i < bytes)
			init_path(&((*tab)[i]), rooms);
		(*tab)[i] = NULL;
	}
	i = 0;
	while ((*tab)[i] && (*tab)[i][0] != 1)
		i++;
	if ((*tab)[i])
	{
		cpy_path(&((*tab)[i]), *path);
		free(*path);
	}
	else
	{
		*tab = re_init_table(tab, rooms, bytes);
		add_path(tab, rooms, path);
	}
}
