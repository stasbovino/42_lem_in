/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 18:16:49 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/16 17:50:10 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


int		**init_int_table(char **table, int rooms)
{
	int	**int_table;
	int	i;
	int	j;

	(void)table;
	int_table = (int**)malloc(sizeof(int*) * (rooms + 2));
	i = -1;
	while (++i < (rooms + 2))
		int_table[i] = (int*)malloc(sizeof(int) * (rooms + 2));
	i = 0;
	j = -1;
	while (++j < (rooms + 1))
		int_table[0][j] = j;
	int_table[0][j] = 0;
	while (++i < (rooms + 1))
		int_table[i][0] = i;
	int_table[i][0] = 0;
	i = 0;
	while (++i < (rooms + 1))
	{
		j = 0;
		while (++j < (rooms + 1))
			int_table[i][j] = 0;
		int_table[i][j] = 0;
	}
	j = 0;
	while (++j < (rooms + 2))
		int_table[i][j] = 0;
	return (int_table);
}

void	print_tab(int **int_table, int rooms)
{
	int i;
	int j;

	i = -1;
	ft_printf("TABLE:\n");
	while (++i < (rooms + 2))
	{
		j = -1;
		while (++j < (rooms + 2))
			ft_printf("%d ", int_table[i][j]);
		ft_printf("\n");
	}
}

void	free_tables(int ***int_table, char ***table, int rooms)
{
	int i;

	i = -1;
	if (int_table)
	{
		while (++i < (rooms + 2))
			free((*int_table)[i]);
		free(*int_table);
		i = -1;
	}
	if (table)
	{
		while (++i < (rooms + 1))
			free((*table)[i]);
		free(*table);
	}
}


char	*get_next_link(char **input, int size)
{
	static int	last = 0;
	int			ret;

	if (last == 0)
	{
		while (find_no_link(input[last]))
			last++;
		last--;
	}
	while (++last < size)
	{
		ret = find_no_link(input[last]);
		if (ret == 0)
			return (input[last]);
		if (ret == 1)
			return (NULL);
	}
	return (NULL);
}
/*
void	create_links(int ***int_table, char **table, char **input)
{
	int **tmp;
	int	i;
	int	j;

	tmp = *int_table;
	i = -1;
	j = -1;
	while (input[
}
*/

int		set_start_and_end(char **input, int size, char ***table)
{
	int i;
	int	start;
	int	end;

	start = 0;
	end = 0;
	i = -1;
	while (++i < size)
	{
		if (input[i][0] == '#' && input[i][1] == '#')
		{
			if (ft_strstr(input[i], "start"))
			{
				start++;
				if (start == 2)
					return (1);
			}
			else if (ft_strstr(input[i], "end"))
			{
				end++;
				if (end == 2)
					return (1);
			}
		}
	}
}

int		error_graph(char ***table, int ***int_table, int rooms)
{
	free_tables(int_table, table, rooms);
	return (1);
}

int		create_table(char **input, int size)
{
	int		rooms;
	char	**table;
	int		**int_table;
	int		i;

	rooms = count_rooms(input, size);
	ft_printf("rooms: %d\n", rooms);
	if (rooms == 0)
		return (1);
	table = (char**)malloc(sizeof(char*) * (rooms + 1));
	i = -1;
	while (++i < rooms)
		table[i] = get_next_room_name(input, size);
	table[i] = NULL;
	if (set_start_and_end(input, size, &table))
		return (error_graph(&table, NULL, rooms));
	i = -1;
	ft_printf("ROOMS:\n");
	while (++i < (rooms + 1))
		ft_printf("%d. %s\n", i + 1, table[i]);
	int_table = init_int_table(table, rooms);
	print_tab(int_table, rooms);
//	create_links(&int_table, table, input);
	free_tables(&int_table, &table, rooms);
	return (0);
}
