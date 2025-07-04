/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: .frnki   <frnki@frnki.dev>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 04:20:42 by .frnki            #+#    #+#             */
/*   Updated: 2025/05/21 16:20:42 by .frnki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static int	run_all(t_table *table)
{
	unsigned int	i;

	if (table->num_of_phil == 1)
		return (solo_adventure(&table->philos[0]), 0);
	table->t_start = check_time();
	i = 0;
	while (i < table->num_of_phil)
		table->philos[i++].t_last = table->t_start;
	if (create_threads(table))
		return (1);
	return (0);
}

static int	init_all(int argc, char **argv, t_table *table)
{
	if (check_args(argc, argv) || init_table(argc, argv, table))
		return (1);
	if (set_philos(table) || set_t_start(table))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (init_all(argc, argv, table) || run_all(table))
		return (destroy_table(table), 1);
	destroy_table(table);
	return (0);
}