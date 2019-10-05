/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 19:35:29 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/05 22:47:02 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	define_rooms(int *s)
{
	int i;

	i = 1;
	while (s[i + 1] != 0)
		i++;
	return (s[i] * 2);
}

int			**double_table(int **begin)
{
	int i;
	int j;
	int n;
	int k;
	int **new;
	int rooms;
	int old_rooms;

	rooms = define_rooms(begin[0]);
	old_rooms = rooms / 2;
	if (!(new = init_int_table(rooms)))
		return (NULL);
	i = 1;
	j = 0;
	n = 0;
	k = 0;
	while (i < rooms)
	{
		new[i][i + 1] = 1;
		new[i + 1][i] = 1;
		i += 2;
	}
	i = 0;
	while (++i < (old_rooms + 1))
	{
		j = 0;
		while (++j < (old_rooms + 1))
		{
			if (begin[i][j] == 1)
			{
				if (j < i)
				{
					new[i * 2 - 1][j * 2] = 1;
				}
				else if (j > i)
				{
					new[i * 2][j * 2 - 1] = 1;
				}
			}
		}
	}
	return (new);
}
