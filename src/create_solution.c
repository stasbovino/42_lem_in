/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_solution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:46:48 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/08 01:09:40 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char		*create_str(int n, char *room)
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

int			print_solution(t_graph *graph, int *flows)
{
	char **turns;
	int i;
	int j;
	int n;
	int start;
	int curr;
	char *str;
	int need;

	i = -1;
	need = (graph->paths)[0][0] / 2 - 1 + flows[0];
	if (!(turns = (char**)malloc(sizeof(char*) * need)))
		return (1);
	while (++i < (need - 1))
		if (!(turns[i] = ft_strnew(0)))
			return (free_turns(&turns, i));
	turns[i] = NULL;
	i = -1;
	curr = 1;
	while (flows[++i] != -1)
	{
		start = -1;
		while (flows[i] > 0)
		{
			j = 4;
			start++;
			n = start;
			while (j <= (graph->paths)[i][0])
			{
				if (!(str = create_str(curr, (graph->list)[(graph->paths)[i][j] / 2 - 1])))
					return (free_turns(&turns, need));
				if (!(turns[n] = ft_strrejoin(turns[n], str)))
				{
					free(str);
					return (free_turns(&turns, need));
				}
				n++;
				j += 2;
			}
			flows[i]--;
			curr++;
		}
	}
	i = -1;
	while (turns[++i])
		ft_printf("%s\n", turns[i]);
	ft_printf("TOTAL: %d\n", need - 1);
	return (0);
}

int			create_solution(t_graph **graph, int **table, int rooms)
{
	int	*path;
	int ants;
	int n;
	int *flows;

	if (find_shortest_path(table, rooms, &path))
		return (2);
	n = 0;
	ants = (*graph)->ants;
	while (path)
	{
		n++;
		table[path[2]][path[3]] = 0;
		if (add_path(&((*graph)->paths), rooms * 2, &path))
			return (2);
		if ((find_shortest_path(table, rooms, &path)) == 2)
			return (2);
	}
	print_paths((*graph)->paths);
	if (!(flows = create_flows((*graph)->paths, n, ants)))
		return (2);
	if (print_solution(*graph, flows))
	{
		free(flows);
		return (2);
	}
	return (0);
}
