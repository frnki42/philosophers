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

static int	init_all(int argc, char **argv, t_table *table, t_philo **philo)
{
	unsigned int	i;

	if (check_args(argc, argv))
		return (1);
	if (init_table(argc, argv, table))
		return (1);
	*philo = malloc(sizeof(t_philo) * table->num_of_phil);
	if (!*philo)
		return (destroy_table(table), 1);
	if (init_philo(table, *philo))
		return (destroy_table(table), free(*philo), 1);
	if (set_t_start(table, *philo))
		return (destroy_table(table), free(*philo), 1);
	i = 0;
	while (i < table->num_of_phil)
		(*philo)[i++].t_last = table->t_start;
	return (0);
}

static int	run_all(t_table *table, t_philo *philo)
{
	if (table->num_of_phil == 1)
		return (solo_adventure(philo), 0);
	if (create_threads(philo, table))
		return (1);
	join_threads(table, philo);
	return (0);
}

static void	clean_up(t_table *table, t_philo *philo)
{
	destroy_philos(philo, table->num_of_phil);
	destroy_table(table);
	free(philo);
}

int	main(int argc, char **argv)
{
	t_table		table;
	t_philo		*philo;

	if (init_all(argc, argv, &table, &philo))
		return (1);
	if (run_all(&table, philo))
		return (1);
	clean_up(&table, philo);
	return (0);
}
