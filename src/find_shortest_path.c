#include "lem_in.h"

static void	pop_from_queue(int **queue)
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

static void	push_to_queue(int **queue, int i)
{
	int n;

	n = 0;
	while ((*queue)[n] != 0)
		n++;
	(*queue)[n] = i;
	(*queue)[n + 1] = 0;
}

static int	create_path(int **s, int rooms, int *visited)
{
	int j;
	int	n;
	int	*path;
	int	len;

	if (init_path(&path, rooms))
		return (1);
	if (init_path(s, rooms))
	{
		free(path);
		return (1);
	}
	j = rooms - 1;
	path[0] = rooms;
	n = 1;
	while (j != 0)
	{
		path[n] = visited[j];
		j = visited[j] - 1;
		n++;
	}
	len = 0;
	while (path[len] != 0)
		len++;
	n = 0;
	(*s)[n] = len;
	while (len > 0)
		(*s)[++n] = path[--len];
	free(path);
	return (0);
}

int			find_shortest_path(t_graph *graph, int **s)
{
	int	*queue;
	int	*visited;
	int	j;
	int	i;

	if (init_path(&queue, graph->rooms - 1))
		return (2);
	queue[1] = 0;
	if (init_path(&visited, graph->rooms - 1))
	{
		free(queue);
		return (2);
	}
	visited[0] = 1;
	visited[1] = 0;
	j = 0;
	while (queue[0] != 0)
	{
		i = queue[0];
		j = 0;
/*		ft_printf("before pop:\n");
		print_queue(queue);
*/		pop_from_queue(&queue);
/*		ft_printf("poped:\n");
		print_queue(queue);
*/		while (++j < (graph->rooms + 2))
		{
			if ((graph->table)[i][j] == 1)
			{
				if (visited[j - 1] == 0)
				{
					visited[j - 1] = i;
					push_to_queue(&queue, j);
/*					ft_printf("pushed:\n");
					print_queue(queue);
*/					if (j == graph->rooms)
					{
//						ft_printf("\x1b[32mfounded!\x1b[0m\n");
						if (create_path(s, graph->rooms, visited))
						{
							free(visited);
							free(queue);
							return (2);
						}
						free(visited);
						free(queue);
						return (0);
					}
				}
			}
		}
/*		ft_printf("new queue:\n");
		print_queue(queue);
		ft_printf("\n");
*/	}
	*s = NULL;
	free(visited);
	free(queue);
	return (1);
}
