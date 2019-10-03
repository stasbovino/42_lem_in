/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:11:08 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/03 17:11:52 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
