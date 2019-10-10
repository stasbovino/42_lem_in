#include "lem_in.h"

int	free_solution(int ***table, int ***begin, int **path, int ret)
{
	int rooms;
	int **tab;

	rooms = 1;
	tab = *table;
	while (tab[0][rooms] != 0)
		rooms++;
	rooms--;
	if (path && *path)
		free(*path);
	if (table)
		free_tables(table, NULL, rooms);
	if (begin)
		free_tables(begin, NULL, rooms);
	restore_table(NULL, rooms, 1);
	return (ret);
}

int	free_solution_and_flows(int ***table, int ***begin, int **path, int **flows)
{
	int rooms;
	int **tab;

	rooms = 1;
	tab = *table;
	while (tab[0][rooms] != 0)
		rooms++;
	rooms--;
	if (path && *path)
		free(*path);
	if (flows && *flows)
		free(*flows);
	if (table)
		free_tables(table, NULL, rooms);
	if (begin)
		free_tables(begin, NULL, rooms);
	restore_table(NULL, rooms, 1);
	return (-1);
}

int	init_search(int ***table, int ***begin, int **path, t_graph *graph)
{
	int ret;
	int rooms;

	rooms = graph->rooms * 2;
	if (!(*table = double_table(graph->table)))
		return (2);
	if (!(*begin = tab_dup(*table, rooms)))
		return (free_solution(table, NULL, NULL, 2));
	if (restore_table(*begin, rooms, 0))
		return (free_solution(table, begin, NULL, 2));
	if ((ret = find_shortest_path(*table, rooms, path)) != 0)
			return (free_solution(table, begin, NULL, ret));
	return (0);
}

int	end_of_find_solution(int ret)
{
	if (ret == 1)
		return (-2);
	return (0);
}
