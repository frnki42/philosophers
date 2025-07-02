/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: .frnki   <frnki@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:20:42 by .frnki            #+#    #+#             */
/*   Updated: 2025/05/21 16:20:42 by .frnki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

// hello world!
int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philo;

	if (check_args(argc, argv) || init_table(argc, argv, &table))
		return (1);
	philo = malloc(sizeof(t_philo) * table.num_of_phil);
	if (!philo)
		return (destroy_table(&table), 1);
	init_philo(&table, philo);
	if (set_t_start(&table, philo) || create_threads(philo, &table))
		return (1);
	join_threads(&table, philo);
	printf("%i\n", philo[0].ate);
	destroy_table(&table);
	free(philo);
	return (0);
}
