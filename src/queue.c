/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:11:08 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/09 22:25:49 by tiyellow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	doop_helper(int *begin, int *end, int *elem)
{
	*begin = 0;
	*end = 0;
	*elem = 1;
}

void		do_queue_op(int *queue, int *i, int op, int rooms)
{
	static int begin = 0;
	static int end = 0;
	static int elem = 1;

	if (op == 0)
		doop_helper(&begin, &end, &elem);
	if (op == -1)
	{
		*i = queue[begin];
		queue[begin] = 0;
		elem--;
		begin++;
		begin = begin == rooms ? 0 : begin;
		end = elem == 0 ? 0 : end;
		begin = elem == 0 ? 0 : begin;
		end = elem == 1 ? begin + 1 : end;
	}
	else if (op == 1)
	{
		queue[end] = *i;
		elem++;
		end++;
		end = end == rooms ? 0 : end;
	}
}

void		pop_from_queue(int **queue)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*queue)[j] != 0)
		j++;
	while (i != j)
	{
		(*queue)[i] = (*queue)[i + 1];
		i++;
	}
}

void		push_to_queue(int **queue, int i)
{
	int n;

	n = 0;
	while ((*queue)[n] != 0)
		n++;
	(*queue)[n] = i;
	(*queue)[n + 1] = 0;
}
