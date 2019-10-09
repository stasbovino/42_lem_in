/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_flows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:27:20 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/09 23:21:18 by gwyman-m         ###   ########.fr       */
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

static int	init_flows(int **flows, int n)
{
	int i;

	if (!(*flows = (int*)malloc(sizeof(int) * (n + 1))))
		return (1);
	i = -1;
	while (++i < n)
		(*flows)[i] = 0;
	(*flows)[i] = -1;
	return (0);
}

static void	set_new_highscore(int **paths, int *k, int *begin)
{
	int i;
	int t;

	i = 0;
	t = *k;
	while (paths[i] && paths[i][0] != 1 && paths[i][0] <= paths[t][0])
		i++;
	*k = i;
	*begin = -1;
}

int			*create_flows(int **paths, int n, int ants)
{
	int i;
	int *f;
	int k;

	if (init_flows(&f, n))
		return (NULL);
	k = 0;
	set_new_highscore(paths, &k, &i);
	while (ants > 0 && ++i < k)
	{
		if (paths[k] && paths[k][0] != 1 && (paths[i][0] / 2 - 2 + f[i]) == (paths[k][0] / 2 - 2))
			if (i + 1 != k)
			{
			}
/*		if (paths[k] && paths[k][0] != 1 && i + 1 != k
				&& (paths[i][0] / 2 - 2 + f[i]) == (paths[k][0] / 2 - 2))
			continue ;
		if (i + 1 == k)
		{
			if (paths[k] && paths[k][0] != 1
					&& (paths[i][0] / 2 - 2 + f[i]) == (paths[k][0] / 2 - 2))
				set_new_highscore(paths, &k, &i);
			else
			{
				f[i]++;
				ants--;
				i = -1;
			}
			continue ;
		}
*/		f[i]++;
		ants--;
	}
	return (f);
}
