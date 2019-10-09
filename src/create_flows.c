/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_flows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:27:20 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/09 17:41:19 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_flows(int *flows)
{
	int i;

	i = -1;
	while (flows[++i] != -1)
		ft_printf("%d ", flows[i]);
	ft_printf("F\n");
}

int			*create_flows(int **paths, int n, int ants)
{
	int i;
	int *flows;
	int k;

	i = -1;
	if (!(flows = (int*)malloc(sizeof(int) * (n + 1))))
		return (NULL);
	while (++i < n)
		flows[i] = 0;
	flows[i] = -1;
	i = 0;
	while (paths[i] && paths[i][0] != 1 && paths[i][0] == paths[0][0])
		i++;
	k = i;
	i = 0;
	while (ants > 0 && i < k)
	{
		if (paths[k] && paths[k][0] != 1 && i + 1 != k
				&& (paths[i][0] / 2 - 2 + flows[i]) == (paths[k][0] / 2 - 2))
		{
			i++;
			continue ;
		}
		if (i + 1 == k)
		{
			if (paths[k] && paths[k][0] != 1
					&& (paths[i][0] / 2 - 2 + flows[i]) == (paths[k][0] / 2 - 2))
			{
				i = 0;
				while (paths[i] && paths[i][0] != 1 && paths[i][0] <= paths[k][0])
					i++;
				k = i;
				i = 0;
				continue ;
			}
			flows[i]++;
			ants--;
			i = 0;
			continue ;
		}
		flows[i]++;
		ants--;
		i++;
	}
//	print_flows(flows);
	return (flows);
}
