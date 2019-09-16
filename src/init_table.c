/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 18:16:49 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/16 16:15:36 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		find_no_room(char *s)
{
	int i;

	i = -1;
	if (s[0] == '#')
		return (2);
	while (s[++i])
		if (s[i] == '-')
			return (1);
	return (0);
}

int		count_rooms(char **input, int size)
{
	int i;
	int	count;
	int	ret;

	count = 0;
	i = 0;
	while (++i < size)
	{
		ret = find_no_room(input[i]);
		if (ret == 1)
			break ;
		if (ret == 0)
			count++;
	}
	return (count);
}

char	*get_first_word(char *input)
{
	int		i;
	int		len;
	char	*word;

	len = 0;
	while (input[len] != ' ')
		len++;
	word = (char*)malloc(sizeof(char) * (len + 1));
	word[len] = '\0';
	i = -1;
	while (++i < len)
		word[i] = input[i];
	return (word);
}

char	*get_next_room_name(char **input, int size)
{
	static int	last = 0;
	int			ret;

	if (last == 0)
	{
		while (input[last][0] == '#' || count_words(input[last]) != 3)
			last++;
		last--;
	}
	while (++last < size)
	{
		ret = find_no_room(input[last]);
		if (ret == 0)
			return (get_first_word(input[last]));
		if (ret == 1)
			return (NULL);
	}
	return (NULL);
}

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
			int_table[i][j] = 1;
	}
	return (int_table);
}

void	print_tab(int **int_table, int rooms)
{
	int i;
	int j;

	i = -1;
	while (++i < (rooms + 2))
	{
		j = -1;
		while (++j < (rooms + 2))
			ft_printf("%d ", int_table[i][j]);
		ft_printf("\n");
	}
}

void	create_links(int ***int_table, char **table, char **input)
{
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
	{
		table[i] = ft_strdup(get_next_room_name(input, size));
	}
	table[i] = NULL;
	i = -1;
	ft_printf("ROOMS:\n");
	while (++i < (rooms + 1))
		ft_printf("%d. %s\n", i, table[i]);
	int_table = init_int_table(table, rooms);
	print_tab(int_table, rooms);
	create_links(&int_table, table, input);
	return (0);
}
