/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:07:36 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/17 20:33:29 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct	s_graph
{
	int			rooms;
	int			ants;
	int			**table;
	char		**list;
	int			x;
	int			y;
	int			**path;
}				t_graph;

void			print_tab(int **int_table, int rooms);
void			print_graph(t_graph *graph);

char			**read_input(int *size);

t_graph			*create_table(char **input, int size);
void			create_links(int ***int_table, char **table,
		char **input, int size);

int				check_link(char *buf);
int				check_valid(char **input, int count, char *buf, int useful);
int				check_isnum(char *num);
int				check_overflow(char *num);
int				check_split(char **input, int count, char ***split, int words);
int				check_start_and_end(char **input, int count);

int				count_words(char *buf);
int				count_rooms(char **input, int size);

int				free_split(char ***split, int words, int ret);
void			free_tables(int ***int_table, char ***table, int rooms);

int				find_no_room(char *s);
int				find_no_link(char *s);

int				get_ants_num(char **input, int size);
char			*get_first_word(char *input);
char			*get_next_room_name(char **input, int size, int opt);
char			*get_next_link(char **input, int size);

int				compare_coords(char *input, char **split);
int				compare_names(char *input, char *name);

#endif
