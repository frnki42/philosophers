/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: .frnki   <frnki@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:20:42 by .frnki            #+#    #+#             */
/*   Updated: 2025/05/21 04:16:20 by .frnki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

// joins threads
void	join_threads(t_table *table, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < table->num_of_phil)
		pthread_join(philo[i++].thread, NULL);
}

// creates one thread, destroys and frees stuff on failure
int	create_thread(t_philo *philo, t_table *table, unsigned int i)
{
	if (pthread_create(&philo[i].thread, NULL, start_routine, &philo[i]))
	{
		printf("# error creating thread. cleaning up & exiting..\n");
		destroy_table(table);
		free(philo);
		return (1);
	}
	return (0);
}

// calls create_thread num_of_phil amount of time
int	create_threads(t_philo *philo, t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->num_of_phil && table->all_alive)
	{
		if (create_thread(philo, table, i++))
			return (1);
	}
	return (0);
}
