/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:45:13 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/09 19:06:04 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	**re_init(char ***input, int count)
{
	char	**new;
	int		i;

	i = 0;
	new = (char**)malloc(sizeof(char*) * (count + 10));
	while (i < count)
	{
		new[i] = ft_strdup((*input)[i]);
		free((*input)[i]);
	}
	free(*input);
	return (new);
}

char	**read_input(int *size)
{
	char	**input;
	char	*buf;
	int		r;
	int		count;

	count = 0;
	r = 0;
	buf = NULL;
	input = (char**)malloc(sizeof(char*) * 10);
	while ((r = get_next_line(0, &buf, 0)))
	{
		if (r == -1)
			return (NULL);
		input[count] = buf;
		if (check_valid(buf, count))
			return (NULL);
		count++;
		if (count % 10 == 0)
			input = re_init(&input, count);
	}
	*size = count;
	return (input);
}

int	main(void)
{
	char	**input;
	int		size;
	int		i;

	i = -1;
	size = 0;
	input = read_input(&size);
	ft_printf("%d\n", size);
	if (input == NULL)
	{
		ft_printf("error\n");
		return (1);
	}
	else
	{
		while (++i < size)
		{
			ft_printf("%s\n", input[i]);
		}
	}
	return (0);
}
