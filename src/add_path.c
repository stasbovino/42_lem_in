/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:58:54 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/02 18:41:01 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		cpy_path(int **dest, int *src)
{
	int		i;

	i = -1;
	while (src[++i] != 0)
		(*dest)[i] = src[i];
}

static int	**free_table(int ***old, int ***new, int i, int bytes)
{
	int j;

	j = -1;
	while (++j < i)
		free((*new)[i]);
	free(*new);
	while (i++ < bytes)
		free((*old)[i]);
	free(*old);
	return (NULL);
}

static int	**re_init_table(int ***old, int rooms, int *bytes)
{
	int **new;
	int	i;
	int	len;

	len = *bytes * 2;
	*bytes = len;
	if (!(new = (int**)malloc(sizeof(int*) * (len + 1))))
		return (NULL);
	i = -1;
	while (++i < len)
	{
		if (!(init_path(&(new[i]), rooms)))
			return (free_table(old, &new, i, *bytes));
		if (i < *bytes)
		{
			cpy_path(&(new[i]), (*old)[i]);
			free((*old)[i]);
		}
	}
	new[i] = NULL;
	free(*old);
	return (new);
}

static int	init_table(int ***tab, int bytes, int rooms)
{
	int i;
	int j;

	i = -1;
	if (!(*tab = (int**)malloc(sizeof(int*) * (bytes + 1))))
		return (1);
	while (++i < bytes)
		if (init_path(&((*tab)[i]), rooms))
		{
			j = -1;
			while (++j < i)
				free((*tab)[i]);
			free(*tab);
			return (1);
		}
	(*tab)[i] = NULL;
	return (0);
}

int			add_path(int ***tab, int rooms, int **path)
{
	int			i;
	static int	bytes = 10;

	if (*tab == NULL)
		if (init_table(tab, bytes, rooms))
			return (1);
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
		if (!(*tab = re_init_table(tab, rooms, &bytes)))
			return (1);
		if (add_path(tab, rooms, path))
			return (1);
	}
	return (0);
}
