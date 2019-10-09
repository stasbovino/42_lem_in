/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:11:08 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/09 17:15:43 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	do_queue_op(int *queue, int *i, int op, int rooms)
{
	static int begin = 0;
	static int end = 0;
	static int elem = 1;

	if (op == 0)
	{
		begin = 0;
		end = 0;
		elem = 1;
		return ;
	}
	if (op == -1)
	{
		*i = queue[begin];
		queue[begin] = 0;
		elem--;
		begin++;
		if (begin == rooms)
			begin = 0;
		if (elem == 0)
		{
			end = 0;
			begin = 0;
		}
		else if (elem == 1)
			end = begin + 1;
	}
	else if (op == 1)
	{
		queue[end] = *i;
		elem++;
		end++;
		if (end == rooms)
			end = 0;
	}
}

void	pop_from_queue(int **queue)
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

void	push_to_queue(int **queue, int i)
{
	int n;

	n = 0;
	while ((*queue)[n] != 0)
		n++;
	(*queue)[n] = i;
	(*queue)[n + 1] = 0;
}
