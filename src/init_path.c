/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:38:15 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/18 22:38:48 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		init_path(int **path, int rooms)
{
	int i;

	*path = (int*)malloc(sizeof(int) * (rooms + 2));
	i = -1;
	while (++i < (rooms + 2))
		(*path)[i] = 0;
}
