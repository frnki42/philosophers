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
		pthread_mutex_lock(&philo->table->alive_lock);
		table->all_alive = 0;
		pthread_mutex_lock(&philo->table->alive_lock);
		j = 0;
		while (j < i)
			pthread_join(philo[j++].thread, NULL);
		destroy_philos(philo, i);
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
	pthread_t	monitor_thread;

	i = -1;
	while (++i < table->num_of_phil)
	{
		pthread_mutex_lock(&table->alive_lock);
		if (!table->all_alive)
		{
			pthread_mutex_unlock(&table->alive_lock);
			break ;
		}
		pthread_mutex_unlock(&table->alive_lock);
		if (create_thread(philo, table, i))
			return (1);
		if (i % 2 == 0)
			usleep(100);
	}
	if (pthread_create(&monitor_thread, NULL, monitor, philo))
	{
		printf("# error creating monitor thread.\n");
		pthread_mutex_lock(&table->alive_lock);
		table->all_alive = 0;
		pthread_mutex_unlock(&table->alive_lock);
		join_threads(table, philo);
		destroy_philos(philo, table->num_of_phil);
		destroy_table(table);
		free(philo);
		return (1);
	}
	pthread_detach(monitor_thread);
	return (0);
}
