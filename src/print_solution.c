/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 21:36:56 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/10 16:55:36 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	*c_s(int n, char *room)
{
	char	*s;
	int		i;
	int		j;
	int		numlen;
	int		roomlen;

	numlen = ft_numlen((size_t)n);
	roomlen = ft_strlen(room);
	if (!(s = ft_strnew(3 + numlen + roomlen)))
		return (NULL);
	s[0] = 'L';
	i = numlen + 1;
	while (numlen)
	{
		s[numlen] = n % 10 + '0';
		n /= 10;
		numlen--;
	}
	s[i] = '-';
	j = 0;
	while (roomlen--)
		s[++i] = room[j++];
	s[++i] = ' ';
	return (s);
}

static int	free_turns(char ***turns, int i)
{
	int j;

	j = -1;
	while (++j < i)
		if ((*turns)[j])
			free((*turns)[j]);
	free(*turns);
	return (1);
}

static int	init_print_sol(char ***turns, int need)
{
	int i;

	i = -1;
	if (1 || !(*turns = (char**)malloc(sizeof(char*) * need)))
		return (1);
	while (++i < (need - 1))
		if (!((*turns)[i] = ft_strnew(0)))
			return (free_turns(turns, i));
	(*turns)[i] = NULL;
	return (0);
}

static int	add_flow(t_graph *graph, int *flows, char ***turns, int i)
{
	int			j;
	int			n;
	static int	curr = 1;
	int			start;
	char		*str;

	start = -1;
	while (flows[i]-- > 0)
	{
		j = 4;
		n = ++start;
		while (j <= (graph->paths)[i][0])
		{
			if (!(str = c_s(curr, (graph->list)[(graph->paths)[i][j] / 2 - 1])))
				return (1);
			(*turns)[n] = ft_strrejoin((*turns)[n], str);
			free(str);
			if (!((*turns)[n]))
				return (1);
			n++;
			j += 2;
		}
		curr++;
	}
	return (0);
}

int			print_solution(t_graph *graph, int *flows)
{
	char	**turns;
	int		i;
	int		need;

	need = (graph->paths)[0][0] / 2 - 1 + flows[0];
	if (init_print_sol(&turns, need))
		return (1);
	i = -1;
	while (flows[++i] != -1)
		if (add_flow(graph, flows, &turns, i))
			return (free_turns(&turns, need));
	i = -1;
	while (turns[++i])
	{
//		ft_putstr(turns[i]);
//		ft_putchar('\n');
	}
	ft_printf("TOTAL: \x1b[32m%d\x1b[0m\n", need - 1);
	free_turns(&turns, need);
	return (0);
}
