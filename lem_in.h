/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:07:36 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/11 19:04:38 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "limits.h"
# define SIZE 4000

typedef struct	s_graph
{
	int			rooms;
	int			ants;
	int			**table;
	char		**list;
	int			**paths;
	int			*flows;
}				t_graph;

void			print_tab(int **int_table, int rooms);
void			print_graph(t_graph *graph);
void			print_path(int *path);
void			print_paths(int **paths);
void			print_queue(int *queue);
int				print_solution(t_graph *graph, int *flows);
int				print_ez_solution(t_graph *graph);

int				**tab_dup(int **table, int rooms);
int				*dup_path(int *path, int rooms);
void			cpy_path(int **dest, int *src);
void			reweight(int **table, int *path);
void			restruct_table(int **table, int **begin, int rooms);
int				restore_table(int **begin, int rooms, int opt);
int				back_weight(int **table, int *path);

int				find_shortest_path(int **table, int rooms, int **s);

t_graph			*init_graph(char **table, int **int_table, int rooms, int ants);
int				**init_int_table(int rooms);
int				init_path(int **path, int rooms);
int				add_path(int ***tab, int rooms, int **path);

char			**read_input(int *size, int useful, int count);

t_graph			*create_table(char **input, int size);
int				**allocate_table(int rooms);
int				**double_table(int **begin);

int				check_split(char **input, int count, char ***split, int words);
int				check_start_and_end(char **input, int count);
int				check_link(char *buf);
int				check_valid(char **input, int count, char *buf, int useful);
int				check_ants(char *buf);

int				check_isnum(char *num);
int				check_overflow(char *num);
int				count_words(char *buf);
int				count_rooms(char **input, int size);
int				count_chars(char *s);

int				create_links(int ***int_table, char **table,
		char **input, int size);

void			*free_all(char ***table, int ***int_table, int rooms, int opt);
int				free_split(char ***split, int words, int ret);
void			free_tables(int ***int_table, char ***table, int rooms);
void			free_input(char ***input, int size);
void			free_graph(t_graph **graph);
void			free_paths(int ***paths);

int				free_solution(int ***table, int ***begin, int **path, int ret);
int				free_solution_and_flows(int ***table, int ***begin,
		int **path, int **flows);
int				init_search(int ***table, int ***begin,
		int **path, t_graph *graph);
int				end_of_find_solution(int ret);

void			do_queue_op(int *queue, int *i, int op, int rooms);
void			pop_from_queue(int **queue);
void			push_to_queue(int **queue, int i);

int				find_no_room(char *s);
int				find_no_link(char *s);

char			*get_first_word(char *input);
char			*get_next_room_name(char **input, int size, int opt);
char			*get_next_link(char **input, int size);
int				get_ants_num(char **input, int size);

int				compare_coords(char *input, char **split);
int				compare_names(char *input, char *name);

int				*create_flows(int **paths, int n, int ants);
int				find_solution(t_graph **graph, int rooms, int *flow, int prev);
int				create_solution(t_graph **graph,
		int **table, int rooms, int **f);

#endif
