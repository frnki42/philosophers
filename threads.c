/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: .frnki   <frnki@frnki.dev>                 +#+  +:+       +#+        */
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
	unsigned int	j;

	if (pthread_create(&philo[i].thread, NULL, start_routine, &philo[i]))
	{
		printf("# error creating thread. cleaning up & exiting..\n");
		table->all_alive = 0;
		j = 0;
		while (j < i)
			pthread_join(philo[j++].thread, NULL);
		destroy_philos(philo, i);
		destroy_table(table);
		return (1);
	}
	return (0);
}

// calls create_thread num_of_phil amount of time
int	create_threads(t_philo *philo, t_table *table)
{
	unsigned int	i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < table->num_of_phil && table->all_alive)
	{
		if (create_thread(philo, table, i))
			return (1);
		if (i % 2 == 0)
			usleep(100);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, philo))
	{
		printf("# error creating monitor thread.\n");
		table->all_alive = 0;
		join_threads(table, philo);
		destroy_philos(philo, table->num_of_phil);
		destroy_table(table);
		return (1);
	}
	pthread_detach(monitor_thread);
	return (0);
}
