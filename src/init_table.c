/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 18:16:49 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/16 23:12:17 by gwyman-m         ###   ########.fr       */
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

void	create_links(int ***int_table, char **table, char **input, int size)
{
	int		i;
	int		j;
	int		a;
	int		b;
	char	**rooms;

	i = 0;
	while (input[i][0] == '#' || !ft_strchr(input[i], '-'))
		i++;
	i--;
	while (++i < size)
	{
		if (input[i][0] == '#')
			continue ;
		rooms = ft_strsplit(input[i], '-');
		j = -1;
		a = 0;
		b = 0;
		while (table[++j])
		{
			if (ft_strcmp(table[j], rooms[0]) == 0)
				a = j + 1;
			else if (ft_strcmp(table[j], rooms[1]) == 0)
				b = j + 1;
			if (a != 0 && b != 0)
				break ;
		}
		(*int_table)[a][b] = 1;
		(*int_table)[b][a] = 1;
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
	i = 0;
	table[0] = get_next_room_name(input, size, 0);
	table[rooms - 1] = get_next_room_name(input, size, rooms - 1);
	while (++i < rooms - 1)
		table[i] = get_next_room_name(input, size, -1);
	table[i + 1] = NULL;
	i = -1;
	ft_printf("ROOMS:\n");
	while (++i < (rooms + 1))
		ft_printf("%d. %s\n", i + 1, table[i]);
	int_table = init_int_table(table, rooms);
	print_tab(int_table, rooms);
	create_links(&int_table, table, input, size);
	print_tab(int_table, rooms);
	free_tables(&int_table, &table, rooms);
	return (0);
}
