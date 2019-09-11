/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:45:13 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/11 18:10:13 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	**re_init(char ***input, int count)
{
	char	**tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tmp = (char**)malloc(sizeof(char*) * (count + 2));
	while (i < count)
	{
		tmp[i] = ft_strdup((*input)[i]);
		free((*input)[i]);
		i++;
	}
	free(*input);
	return (tmp);
}

char	**read_error(char ***input, int count, char **buf)
{
	int i;

	i = 0;
	free(*buf);
	while (i < count)
	{
		free((*input)[i]);
		i++;
	}
	free(*input);
	return (NULL);
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
	input = (char**)malloc(sizeof(char*) * 2);
	while ((r = get_next_line(0, &buf, 0)))
	{
		if (r == -1)
			return (read_error(&input, count, &buf));
		if (check_valid(buf, count))
			return (read_error(&input, count, &buf));
		input[count] = ft_strdup(buf);
		free(buf);
		buf = NULL;
		count++;
		if (count % 2 == 0)
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
		get_next_line(0, NULL, 1);
		return (1);
	}
	else
	{
		while (++i < size)
		{
			ft_printf("%s\n", input[i]);
			free(input[i]);
		}
		free(input);
		get_next_line(0, NULL, 1);
	}
	return (0);
}
