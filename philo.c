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

static int	init_all(int argc, char **argv, t_table *table)
{
	unsigned int	i;

	if (check_args(argc, argv) || init_table(argc, argv, table))
		return (1);
	if (set_philos(table) || set_t_start(table))
		return (destroy_table(table), 1);
	i = 0;
	while (i < table->num_of_phil)
		table->philos[i++].t_last = table->t_start;
	return (0);
}

static int	run_all(t_table *table)
{
	if (table->num_of_phil == 1)
		return (solo_adventure(&table->philos[0]), 0);
	if (create_threads(table))
		return (destroy_table(table), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		*table;

	if (init_all(argc, argv, table) || run_all(table))
		return (1);
	destroy_table(table);
	return (0);
}